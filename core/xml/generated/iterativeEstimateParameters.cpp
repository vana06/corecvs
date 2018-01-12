/**
 * \file iterativeEstimateParameters.cpp
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 */

#include <vector>
#include <stddef.h>
#include "iterativeEstimateParameters.h"

/**
 *  Looks extremely unsafe because it depends on the order of static initialization.
 *  Should check standard if this is ok
 *
 *  Also it's not clear why removing "= Reflection()" breaks the code;
 **/

namespace corecvs {
template<>
Reflection BaseReflection<IterativeEstimateParameters>::reflection = Reflection();
template<>
int BaseReflection<IterativeEstimateParameters>::dummy = IterativeEstimateParameters::staticInit();
} // namespace corecvs 

SUPPRESS_OFFSET_WARNING_BEGIN


using namespace corecvs;

int IterativeEstimateParameters::staticInit()
{

    ReflectionNaming &nameing = naming();
    nameing = ReflectionNaming(
        "Iterative Estimate Parameters",
        "Iterative Estimate Parameters",
        ""
    );

     getReflection()->objectSize = sizeof(IterativeEstimateParameters);
     

    IntField* field0 = new IntField
        (
          IterativeEstimateParameters::LIMIT_SAMPLES_ID,
          offsetof(IterativeEstimateParameters, mLimitSamples),
          -1,
          "Limit Samples",
          "Limit Samples",
          "Limit Samples",
          true,
         -1,
         99999999
        );
    fields().push_back(field0);
    /*  */ 
    IntField* field1 = new IntField
        (
          IterativeEstimateParameters::ITERATIONS_NUMBER_ID,
          offsetof(IterativeEstimateParameters, mIterationsNumber),
          5,
          "Iterations Number",
          "Iterations Number",
          "Iterations Number",
          true,
         0,
         9999999
        );
    fields().push_back(field1);
    /*  */ 
    BoolField* field2 = new BoolField
        (
          IterativeEstimateParameters::USE_INITIAL_ID,
          offsetof(IterativeEstimateParameters, mUseInitial),
          true,
          "Use initial",
          "Use initial",
          "Use initial"
        );
    field2->widgetHint=BaseField::CHECK_BOX;
    fields().push_back(field2);
    /*  */ 
    DoubleField* field3 = new DoubleField
        (
          IterativeEstimateParameters::INITIAL_SIGMA_ID,
          offsetof(IterativeEstimateParameters, mInitialSigma),
          5,
          "Initial Sigma",
          "Initial Sigma",
          "Initial Sigma",
          true,
         0,
         1e+07
        );
    field3->widgetHint=BaseField::SPIN_BOX;
    field3->precision=2;
    fields().push_back(field3);
    /*  */ 
    DoubleField* field4 = new DoubleField
        (
          IterativeEstimateParameters::SIGMA_FACTOR_ID,
          offsetof(IterativeEstimateParameters, mSigmaFactor),
          0.9,
          "Sigma Factor",
          "Sigma Factor",
          "Sigma Factor",
          true,
         0,
         1
        );
    field4->widgetHint=BaseField::SPIN_BOX;
    field4->precision=5;
    fields().push_back(field4);
    /*  */ 
    ReflectionDirectory &directory = *ReflectionDirectoryHolder::getReflectionDirectory();
    directory[std::string("Iterative Estimate Parameters")]= &reflection;
   return 0;
}
int IterativeEstimateParameters::relinkCompositeFields()
{
   return 0;
}

SUPPRESS_OFFSET_WARNING_END


