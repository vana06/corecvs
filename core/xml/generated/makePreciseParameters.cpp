/**
 * \file makePreciseParameters.cpp
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 * Generated from precise.xml
 */

#include <vector>
#include <stddef.h>
#include "makePreciseParameters.h"

/**
 *  Looks extremely unsafe because it depends on the order of static initialization.
 *  Should check standard if this is ok
 *
 *  Also it's not clear why removing "= Reflection()" breaks the code;
 **/

namespace corecvs {
#if 0
template<>
Reflection BaseReflection<MakePreciseParameters>::reflection = Reflection();
template<>
int BaseReflection<MakePreciseParameters>::dummy = MakePreciseParameters::staticInit();
#endif
} // namespace corecvs 

SUPPRESS_OFFSET_WARNING_BEGIN


using namespace corecvs;

int MakePreciseParameters::staticInit(corecvs::Reflection *toFill)
{
    if (toFill == NULL || toFill->objectSize != 0) {
        SYNC_PRINT(("staticInit(): Contract Violation in <MakePreciseParameters>\n"));
         return -1;
    }

    toFill->name = ReflectionNaming(
        "Make Precise Parameters",
        "Make Precise Parameters",
        ""
    );

     toFill->objectSize = sizeof(MakePreciseParameters);
     

    BoolField* field0 = new BoolField
        (
          MakePreciseParameters::SHOULD_MAKE_PRECISE_ID,
          offsetof(MakePreciseParameters, mShouldMakePrecise),
          false,
          "Should Make Precise",
          "Should Make Precise",
          "Should Make Precise"
        );
    field0->widgetHint=BaseField::CHECK_BOX;
    toFill->fields.push_back(field0);
    /*  */ 
    EnumField* field1 = new EnumField
        (
          MakePreciseParameters::ALGORITHM_ID,
          offsetof(MakePreciseParameters, mAlgorithm),
          0,
          "Algorithm",
          "Algorithm",
          "Algorithm",
          new EnumReflection(3
          , new EnumOption(0,"KLT")
          , new EnumOption(1,"KLT Float")
          , new EnumOption(2,"KLT Fast")
          )
        );
    field1->widgetHint=BaseField::COMBO_BOX;
    toFill->fields.push_back(field1);
    /*  */ 
    EnumField* field2 = new EnumField
        (
          MakePreciseParameters::INTERPOLATION_ID,
          offsetof(MakePreciseParameters, mInterpolation),
          0,
          "Interpolation",
          "Interpolation",
          "Interpolation",
          new EnumReflection(3
          , new EnumOption(0,"Bilinear")
          , new EnumOption(1,"Spline")
          , new EnumOption(2,"Polynom")
          )
        );
    field2->widgetHint=BaseField::COMBO_BOX;
    toFill->fields.push_back(field2);
    /*  */ 
    IntField* field3 = new IntField
        (
          MakePreciseParameters::KLT_ITERATIONS_ID,
          offsetof(MakePreciseParameters, mKLTIterations),
          0,
          "KLT iterations",
          "KLT iterations",
          "KLT iterations",
          true,
         1,
         100,
         1
        );
    toFill->fields.push_back(field3);
    /*  */ 
    IntField* field4 = new IntField
        (
          MakePreciseParameters::KLT_RADIUS_H_ID,
          offsetof(MakePreciseParameters, mKLTRadiusH),
          0,
          "KLT Radius H",
          "KLT Radius H",
          "KLT Radius H",
          true,
         1,
         100,
         1
        );
    toFill->fields.push_back(field4);
    /*  */ 
    IntField* field5 = new IntField
        (
          MakePreciseParameters::KLT_RADIUS_W_ID,
          offsetof(MakePreciseParameters, mKLTRadiusW),
          0,
          "KLT Radius W",
          "KLT Radius W",
          "KLT Radius W",
          true,
         1,
         100,
         1
        );
    toFill->fields.push_back(field5);
    /*  */ 
    DoubleField* field6 = new DoubleField
        (
          MakePreciseParameters::KLT_THRESHOLD_ID,
          offsetof(MakePreciseParameters, mKLTThreshold),
          0,
          "KLT Threshold",
          "KLT Threshold",
          "KLT Threshold",
          true,
         1,
         100,
         1
        );
    field6->widgetHint=BaseField::SPIN_BOX;
    field6->precision=2;
    toFill->fields.push_back(field6);
    /*  */ 
    ReflectionDirectory &directory = *ReflectionDirectoryHolder::getReflectionDirectory();
    directory[std::string("Make Precise Parameters")]= toFill;
   return 0;
}
int MakePreciseParameters::relinkCompositeFields()
{
   return 0;
}

SUPPRESS_OFFSET_WARNING_END


