#include "simulation.h"
#include "list"
#include "simobject.h"
#include <ctime>

#include <chrono>

Simulation::Simulation()
{
     //Objects2 =  std::list<SimObject>();
    SimObject kura;
    kura.CountPhysics=true;

    Objects.push_back(kura);
    cout<<Objects.size()<<" before thread"<<endl;
}
void Simulation::Start()
{
    oldTime = std::chrono::high_resolution_clock::now();
    cout<<Objects.size()<<" before thread v2"<<endl;

    std::thread thr([this]()
    {
        cout<<Objects.size()<<" after thread"<<endl;
        cout<<"kek"<<endl;
        while (true)
        {
            newTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(newTime-oldTime);
           // cout<<time_span.count()<<endl;
            for (int i=0;i<Objects.size();i++)
            {
                Objects[i].Tick(time_span.count());
            }
            cout<<Objects[0].coords<<endl;
            frameCounter++;

            /*if (frameCounter%1000==0)

            {
                cout<<"counter - "<<frameCounter<<endl;

            }*/
            oldTime=newTime;
            usleep(3000);
        }

    });
    thr.detach();
}
