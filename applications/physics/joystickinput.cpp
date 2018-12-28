#include "joystickinput.h"
#include "core/utils/global.h"
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <unistd.h>
#include <QBitArray>
#include <bitset>
#include <linux/joystick.h>
#include <fcntl.h>
#include <thread>
#include "joystickinput.h"
#include "time.h"
#include <fstream>

using namespace std;


JoyStickInput::JoyStickInput(int &_yaw_value, int &_roll_value, int &_pitch_value, int &_throttle_value, int &_CH5_value, int &_CH6_value, int &_CH7_value,  int &_CH8_value )
    : yaw_value(_yaw_value) , roll_value(_roll_value),pitch_value(_pitch_value), throttle_value(_throttle_value),CH5_value(_CH5_value),CH6_value(_CH6_value),CH7_value(_CH7_value),CH8_value(_CH8_value)
{




}

void JoyStickInput::Start()
{
    StartJoyStickMode();
}

//JOYSTICKs PART

/**
 * Reads a joystick event from the joystick device.
 *
 * Returns 0 on success. Otherwise -1 is returned.
 */
int read_event(int fd, struct js_event *event)
{
    ssize_t bytes;

    bytes = read(fd, event, sizeof(*event));

    if (bytes == sizeof(*event))
        return 0;

    /* Error, could not read full event. */
    return -1;
}

/**
 * Returns the number of axes on the controller or 0 if an error occurs.
 */
size_t get_axis_count(int fd)
{
    __u8 axes;

    if (ioctl(fd, JSIOCGAXES, &axes) == -1)
        return 0;

    return axes;
}

/**
 * Returns the number of buttons on the controller or 0 if an error occurs.
 */


size_t get_button_count(int fd)
{
    __u8 buttons;
    if (ioctl(fd, JSIOCGBUTTONS, &buttons) == -1)
        return 0;

    return buttons;
}

/**
 * Current state of an axis.
 */
struct axis_state {        short x, y;   };


/**
 * Keeps track of the current axis state.
 *
 * NOTE: This function assumes that axes are numbered starting from 0, and that
 * the X axis is an even number, and the Y axis is an odd number. However, this
 * is usually a safe assumption.
 *
 * Returns the axis that the event indicated.
 */

size_t get_axis_state(struct js_event *event,  JoyStickInput::axis_state axes[3])
{
    size_t axis = event->number / 2;

    if (axis < 3)
    {
        if (event->number % 2 == 0)
            axes[axis].x = event->value;
        else
            axes[axis].y = event->value;
    }

    return axis;
}



void JoyStickInput::StartJoyStickMode()
{
std::thread thr([this]()
{

    const char *device;
    int js;
    struct js_event eventtt;
    device = "/dev/input/js0";
    js = open(device, O_RDONLY);
    if (js == -1)
    {
        perror("Could not open joystick");
        cout<<"Could not open joystick"<<endl;
    }
    else
    {
        CountOfSticks=get_axis_count(js);
        //FrameValuesUpdate();
        cout<<"JS mode has started"<<endl;
        while (read_event(js, &eventtt) == 0)
        {
            autopilotMode=false;
            switch (eventtt.type)
            {
            case JS_EVENT_BUTTON:
                switch (Current_mode)
                {
                    case 0:
                        usial_buttons(eventtt);
                        break;
                    case 1:
                        inertial_buttons(eventtt);
                        break;
                    case 2:
                        casual_buttons(eventtt);
                        break;
                    default: break;
                }


                break;
            case JS_EVENT_AXIS:
                switch (Current_mode)
                {
                    case 0:
                        usial_sticks(eventtt);
                        break;
                    case 1:
                        inertial_sticks(eventtt);
                        break;
                    case 2:
                        casual_sticks(eventtt);
                        break;
                    default: break;
                }

                break;
            default:
                break;
            }
        }
        }
        });
        thr.detach();
 }

void JoyStickInput::usial_buttons(js_event event)
{
    unsigned char seven=7;
    unsigned char six=6;
    unsigned char five=5;
    unsigned char four=4;
    unsigned char three=3;
    unsigned char two=2;
    unsigned char one=1;
    unsigned char zero=0;
    switch (CountOfSticks)
    {

    case 6:                            //Dinput
        if (event.number==seven)                     //arming    //rt
        {
           Start_arming(event.value);
        }
        if (event.number==five  && event.value )      //rb         //turn of copter(if smth goes wery wery wrong)
        {
            disconnect_from_copter();
        }
        if (event.number==one && event.value)         //a
        {
            if (!recording)
            {
                StartRecord();
            }
            else
            {
                StopRecord();
            }
        }
        break;                          //Xinput
    case 8:

        if (event.number==five  && event.value )      //rb         //turn of copter(if smth goes wery wery wrong)
        {
            disconnect_from_copter();
        }
        if (event.number==zero && event.value)         //a
        {
            if (!recording)
            {
                StartRecord();
            }
            else
            {
                StopRecord();
            }
        }
        break;
    }
}

void JoyStickInput::usial_sticks(js_event event)
{
    const int thr_const=1;
    const int roll_const=10;
    const int pit_const=10;
    const int yaw_const=10;
    size_t axis;

    switch (CountOfSticks)
    {

    case 6:                            //Dinput
         axis = get_axis_state(&event, axes);
        if (axis < 3)
        //printf("Axis %u at (%6d, %6d)\n", axis, axes[axis].x, axes[axis].y);
        {                                                //minimum axis is not 30000, but near
            if (axis==0)
            {
                yaw_value = 1500+axes[axis].x/50/yaw_const;
                throttle_value = 1500-axes[axis].y/50/thr_const;
                if (yaw_value>2100){yaw_value=2099;}
                if (yaw_value<900){yaw_value=901;}
                if (throttle_value>2100){throttle_value=2099;}
                if (throttle_value<900) {throttle_value=901;}
            }
            if (axis==1)
            {
                pitch_value = 1500 - axes[axis].y/50/pit_const;
                roll_value = 1500 + axes[axis].x/50/roll_const;
                if (roll_value>2100){roll_value=2099;}
                if (roll_value<900){roll_value=901;}
                if (pitch_value>2100){pitch_value=2099;}
                if (pitch_value<900){pitch_value=901;}
            }
        }
        break;
    case 8:                            //Xinput
         axis = get_axis_state(&event, axes);
        if (axis < 3)
        //printf("Axis %u at (%6d, %6d)\n", axis, axes[axis].x, axes[axis].y);
        {                                                //minimum axis is not 30000, but near
            if (axis==0)
            {
                yaw_value = 1500+axes[axis].x/50/yaw_const;
                throttle_value = 1500-axes[axis].y/50/thr_const;
                if (yaw_value>2100){yaw_value=2099;}
                if (yaw_value<900){yaw_value=901;}
                if (throttle_value>2100){throttle_value=2099;}
                if (throttle_value<900) {throttle_value=901;}
            }
            if (axis==1)
            {
                roll_value = 1500 + axes[axis].y/50/roll_const;
                if (roll_value>2100){roll_value=2099;}
                if (roll_value<900){roll_value=901;}
            }
            if (axis==2)
            {

                pitch_value = 1500 - axes[axis].x/50/pit_const;
                if (pitch_value>2100){pitch_value=2099;}
                if (pitch_value<900){pitch_value=901;}
                if (axes[axis].y>-20000)
                {
                    Start_arming(true);
                }
                else
                {
                    Start_arming(false);
                }
            }
        }
        break;


    }
}

void JoyStickInput::inertial_buttons(js_event event)
{
    unsigned char seven=7;
    unsigned char six=6;
    unsigned char five=5;
    unsigned char four=4;
    unsigned char three=3;
    unsigned char two=2;
    unsigned char one=1;
    unsigned char zero=0;

    switch (CountOfSticks)
    {

    case 6:                            //Dinput

        if (event.number==seven )                  //rt   //arming
        {
           Start_arming(event.value);
        }
        if (event.number==five  && event.value )    //rb                 //turns of copter(if smth goes very very wrong)
        {
            disconnect_from_copter();
        }
        if (event.number==six  && event.value )     //lt            //  all sticks to zero (if smth goes wrong)
        {
            throttle_value = 1100;
            roll_value = 1500;
            pitch_value = 1500;
            throttle_value_from_JS = 1500;
            yaw_value = 1500;
        }
        if (event.number==four && event.value )      //lb               //Throttle to mid
        {
            throttle_value=mid_Throttle;
            throttle_value_from_JS=1500;
        }
        if (event.number==three && event.value )     //y                //Throttle to mid
        {
             mid_Throttle=throttle_value;
        }
        if (event.number==one && event.value)        //a            //arming
        {
            if (!recording)
            {
                StartRecord();
            }
            else
            {
                StopRecord();
            }
        }
        break;
    case 8:                            //Xinput

        /*if (event.number==seven )                  //rt   //arming
        {
           Start_arming(event.value);
        }
        */
        if (event.number==five  && event.value )    //rb                 //turns of copter(if smth goes very very wrong)
        {
            disconnect_from_copter();
        }
        /*if (event.number==six  && event.value )     //lt            //  all sticks to zero (if smth goes wrong)
        {
            throttle_value = 1100;
            roll_value = 1500;
            pitch_value = 1500;
            throttle_value_from_JS = 1500;
            yaw_value = 1500;
        }
        */
        if (event.number==four && event.value )      //lb               //Throttle to mid
        {
            throttle_value=mid_Throttle;
            throttle_value_from_JS=1500;
        }
        if (event.number==three && event.value )     //y                //Throttle to mid
        {
             mid_Throttle=throttle_value;
        }
        if (event.number==zero && event.value)        //a            //arming
        {
            if (!recording)
            {
                StartRecord();
            }
            else
            {
                StopRecord();
            }
        }
        break;
    }
}

void JoyStickInput::inertial_sticks(js_event event)
{
    const int thr_const=1;
    const int roll_const=10;
    const int pit_const=10;
    const int yaw_const=10;

    size_t axis;

    switch (CountOfSticks)
    {

    case 6:                            //Dinput
         axis = get_axis_state(&event, axes);

        if (axis < 3)
        /* printf("Axis %u at (%6d, %6d)\n", axis, axes[axis].x, axes[axis].y);*/
        {                                                //minimum axis is not 30000, but near
            if (axis==0)
            {
                yaw_value = 1500+axes[axis].x/50/yaw_const;
                throttle_value_from_JS = 1500-axes[axis].y/50/thr_const;
                if (yaw_value>2100){yaw_value=2099;}
                if (yaw_value<900){yaw_value=901;}
                if (throttle_value>2100){throttle_value=2099;}
                if (throttle_value<900) {throttle_value=901;}

            }
            if (axis==1)
            {
                pitch_value = 1500 - axes[axis].y/50/pit_const;
                roll_value = 1500 + axes[axis].x/50/roll_const;
                if (roll_value>2100){roll_value=2099;}
                if (roll_value<900){roll_value=901;}
                if (pitch_value>2100){pitch_value=2099;}
                if (pitch_value<900){pitch_value=901;}
            }
        }
        break;
    case 8:                            //Xinput
         axis = get_axis_state(&event, axes);

        if (axis < 3)
        {                                                //minimum value on axis is -32767 (tested with logitech f710)
            if (axis==0)
            {
                yaw_value = 1500+axes[axis].x/50/yaw_const;
                throttle_value_from_JS = 1500-axes[axis].y/50/thr_const;
                if (yaw_value>2100){yaw_value=2099;}
                if (yaw_value<900){yaw_value=901;}
                if (throttle_value>2100){throttle_value=2099;}
                if (throttle_value<900) {throttle_value=901;}

            }
            if (axis==1)
            {
                roll_value = 1500 + axes[axis].y/50/roll_const;
                if (roll_value>2100){roll_value=2099;}
                if (roll_value<900){roll_value=901;}
                if (axes[axis].x>-29000)
                {
                    throttle_value = 1100;
                    roll_value = 1500;
                    pitch_value = 1500;
                    throttle_value_from_JS = 1500;
                    yaw_value = 1500;
                }

            }
            if (axis==2)
            {

                pitch_value = 1500 - axes[axis].x/50/pit_const;
                if (pitch_value>2100){pitch_value=2099;}
                if (pitch_value<900){pitch_value=901;}
                cout<<"axe lt"<<axes[axis].y<<endl;
                if (axes[axis].y>1000)
                {
                    Start_arming(true);
                }
                else
                {
                    Start_arming(false);
                }
            }
        }
        break;
   }
}

void JoyStickInput::casual_buttons(js_event event)
{

    unsigned char seven=7;
    unsigned char six=6;
    unsigned char five=5;
    unsigned char four=4;
    unsigned char three=3;
    unsigned char two=2;
    unsigned char one=1;
    unsigned char zero=0;

    switch (CountOfSticks)
    {
    case 6:
        if (event.number==five )                    //rb //arming
        {
           Start_arming(event.value);
        }
        if (event.number==four  && event.value )     //lb                //turn of copter(if smth goes wery wery wrong)
        {
            disconnect_from_copter();
        }
        if (event.number==seven  && event.value && !lt_pressed)        //rt
        {
            rt_pressed=true;
            throttle_value=1500;
        }
        if (event.number==seven  && !event.value && !lt_pressed)         //rt
        {
            rt_pressed=false;
            throttle_value=mid_Throttle;
        }
        if (event.number==six  && event.value && !rt_pressed)            //lt
        {
            lt_pressed=true;
            throttle_value=1250;
        }
        if (event.number==six  && !event.value && !rt_pressed)           //lt
        {
            lt_pressed=false;
            throttle_value=mid_Throttle;
        }
        if (event.number==one && event.value)                   //a  //arming
        {
            if (!recording)
            {
                StartRecord();
            }
            else
            {
                StopRecord();
            }
        }
        break;
    case 8:
        if (event.number==five )                    //rb //arming
        {
           Start_arming(event.value);
        }
        if (event.number==four  && event.value )     //lb                //turn of copter(if smth goes wery wery wrong)
        {
            disconnect_from_copter();
        }
        /*if (event.number==seven  && event.value && !lt_pressed)        //rt
        {
            rt_pressed=true;
            throttle_value=1550;
        }
        if (event.number==seven  && !event.value && !lt_pressed)         //rt
        {
            rt_pressed=false;
            throttle_value=mid_Throttle;
        }
        if (event.number==six  && event.value && !rt_pressed)            //lt
        {
            lt_pressed=true;
            throttle_value=1250;
        }
        if (event.number==six  && !event.value && !rt_pressed)           //lt
        {
            lt_pressed=false;
            throttle_value=mid_Throttle;
        }*/
        if (event.number==zero && event.value)                   //a  //arming
        {
            if (!recording)
            {
                StartRecord();
            }
            else
            {
                StopRecord();
            }
        }
        break;

    }
}

void JoyStickInput::casual_sticks(js_event event)
{
    const int thr_const=1;
    const int roll_const=10;
    const int pit_const=10;
    const int yaw_const=10;

    size_t axis;
    switch (CountOfSticks)
    {
    case 6:
        axis = get_axis_state(&event, axes);
        if (axis < 3)
        /* printf("Axis %u at (%6d, %6d)\n", axis, axes[axis].x, axes[axis].y);*/
        {                                                //minimum axis is not 30000, but near
            if (axis==0)
            {
                pitch_value = 1500 - axes[axis].y/50/pit_const;
                roll_value = 1500 + axes[axis].x/50/roll_const;
                if (roll_value>2100){roll_value=2099;}
                if (roll_value<900){roll_value=901;}
                if (pitch_value>2100){pitch_value=2099;}
                if (pitch_value<900){pitch_value=901;}

            }
            if (axis==1)
            {
                yaw_value = 1500 + axes[axis].x/50/yaw_const;
                if (yaw_value>2100){yaw_value=2099;}
                if (yaw_value<900){yaw_value=901;}

            }
        }
        break;
    case 8:
        axis = get_axis_state(&event, axes);
        if (axis < 3)
        /* printf("Axis %u at (%6d, %6d)\n", axis, axes[axis].x, axes[axis].y);*/
        {                                                //minimum axis is not 30000, but near
            if (axis==0)
            {

                roll_value = 1500 + axes[axis].x/50/roll_const;
                if (roll_value>2100){roll_value=2099;}
                if (roll_value<900){roll_value=901;}


            }
            if (axis==1)
            {
                if (axes[axis].x>1000 && !rt_pressed )                          //lt
                {
                    lt_pressed=true;
                    throttle_value=1250;
                }
                if (axes[axis].x<1000 && !rt_pressed )                          //lt
                {
                    lt_pressed=false;
                    throttle_value=mid_Throttle;
                }
                yaw_value = 1500 + axes[axis].y/50/roll_const;
                if (yaw_value>2100){yaw_value=2099;}
                if (yaw_value<900){yaw_value=901;}

            }
            if (axis==2)
            {

                pitch_value = 1500 - axes[axis].x/50/pit_const;
                if (pitch_value>2100){pitch_value=2099;}
                if (pitch_value<900){pitch_value=901;}
                if (axes[axis].y>1000  && !lt_pressed)                            //rt
                {
                    rt_pressed=true;
                    throttle_value=1550;
                }
                if (axes[axis].y<1000  && !lt_pressed)                            //rt
                {
                    rt_pressed=false;
                    throttle_value=mid_Throttle;
                }
            }
        }
        break;


    }
}

void JoyStickInput::Start_arming(bool pressed)
{
    if (pressed)
    {
        printf("##################___ARMING___######################");
        throttle_value=930;
        throttle_value_from_JS=1500;
        CH5_value=1900;
        Arming =true;
    }
    else
    {
        if (Arming)
        {
        throttle_value=1100;
        throttle_value_from_JS=1500;
        Arming=false;
        }
    }
}

void JoyStickInput::disconnect_from_copter()
{
    CH5_value=900;
}

int JoyStickInput::sign(int val)
{
    int result=0;
    if (val >100){result=1;}
    if (val <-100){result=-1;}
    return result;
}


void JoyStickInput::StartRecord()
{
    recording=true;
    recordData =  ControllRecord();

}

void JoyStickInput::StopRecord()
{
    printf("##################___writing___######################");

    recording=false;
    recordData.Save();
}
