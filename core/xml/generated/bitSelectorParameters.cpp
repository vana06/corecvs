/**
 * \file bitSelectorParameters.cpp
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 * Generated from bufferFilters.xml
 */

#include <vector>
#include <stddef.h>
#include "bitSelectorParameters.h"

/**
 *  Looks extremely unsafe because it depends on the order of static initialization.
 *  Should check standard if this is ok
 *
 *  Also it's not clear why removing "= Reflection()" breaks the code;
 **/

namespace corecvs {
#if 0
template<>
Reflection BaseReflection<BitSelectorParameters>::reflection = Reflection();
template<>
int BaseReflection<BitSelectorParameters>::dummy = BitSelectorParameters::staticInit();
#endif
} // namespace corecvs 

SUPPRESS_OFFSET_WARNING_BEGIN


using namespace corecvs;

int BitSelectorParameters::staticInit(corecvs::Reflection *toFill)
{
    if (toFill == NULL || toFill->objectSize != 0) {
        SYNC_PRINT(("staticInit(): Contract Violation in <BitSelectorParameters>\n"));
         return -1;
    }

    toFill->name = ReflectionNaming(
        "Bit Selector Parameters",
        "Bit Selector Parameters",
        ""
    );

     toFill->objectSize = sizeof(BitSelectorParameters);
     

    IntField* field0 = new IntField
        (
          BitSelectorParameters::SHIFT_ID,
          offsetof(BitSelectorParameters, mShift),
          0,
          "shift",
          "shift",
          "shift",
          true,
         -16,
         16,
         1
        );
    toFill->fields.push_back(field0);
    /*  */ 
    BoolField* field1 = new BoolField
        (
          BitSelectorParameters::BIT_0_ID,
          offsetof(BitSelectorParameters, mBit0),
          true,
          "bit 0",
          "bit 0",
          "bit 0"
        );
    field1->widgetHint=BaseField::CHECK_BOX;
    toFill->fields.push_back(field1);
    /*  */ 
    BoolField* field2 = new BoolField
        (
          BitSelectorParameters::BIT_1_ID,
          offsetof(BitSelectorParameters, mBit1),
          true,
          "bit 1",
          "bit 1",
          "bit 1"
        );
    field2->widgetHint=BaseField::CHECK_BOX;
    toFill->fields.push_back(field2);
    /*  */ 
    BoolField* field3 = new BoolField
        (
          BitSelectorParameters::BIT_2_ID,
          offsetof(BitSelectorParameters, mBit2),
          true,
          "bit 2",
          "bit 2",
          "bit 2"
        );
    field3->widgetHint=BaseField::CHECK_BOX;
    toFill->fields.push_back(field3);
    /*  */ 
    BoolField* field4 = new BoolField
        (
          BitSelectorParameters::BIT_3_ID,
          offsetof(BitSelectorParameters, mBit3),
          true,
          "bit 3",
          "bit 3",
          "bit 3"
        );
    field4->widgetHint=BaseField::CHECK_BOX;
    toFill->fields.push_back(field4);
    /*  */ 
    BoolField* field5 = new BoolField
        (
          BitSelectorParameters::BIT_4_ID,
          offsetof(BitSelectorParameters, mBit4),
          true,
          "bit 4",
          "bit 4",
          "bit 4"
        );
    field5->widgetHint=BaseField::CHECK_BOX;
    toFill->fields.push_back(field5);
    /*  */ 
    BoolField* field6 = new BoolField
        (
          BitSelectorParameters::BIT_5_ID,
          offsetof(BitSelectorParameters, mBit5),
          true,
          "bit 5",
          "bit 5",
          "bit 5"
        );
    field6->widgetHint=BaseField::CHECK_BOX;
    toFill->fields.push_back(field6);
    /*  */ 
    BoolField* field7 = new BoolField
        (
          BitSelectorParameters::BIT_6_ID,
          offsetof(BitSelectorParameters, mBit6),
          true,
          "bit 6",
          "bit 6",
          "bit 6"
        );
    field7->widgetHint=BaseField::CHECK_BOX;
    toFill->fields.push_back(field7);
    /*  */ 
    BoolField* field8 = new BoolField
        (
          BitSelectorParameters::BIT_7_ID,
          offsetof(BitSelectorParameters, mBit7),
          true,
          "bit 7",
          "bit 7",
          "bit 7"
        );
    field8->widgetHint=BaseField::CHECK_BOX;
    toFill->fields.push_back(field8);
    /*  */ 
    BoolField* field9 = new BoolField
        (
          BitSelectorParameters::BIT_8_ID,
          offsetof(BitSelectorParameters, mBit8),
          true,
          "bit 8",
          "bit 8",
          "bit 8"
        );
    field9->widgetHint=BaseField::CHECK_BOX;
    toFill->fields.push_back(field9);
    /*  */ 
    BoolField* field10 = new BoolField
        (
          BitSelectorParameters::BIT_9_ID,
          offsetof(BitSelectorParameters, mBit9),
          true,
          "bit 9",
          "bit 9",
          "bit 9"
        );
    field10->widgetHint=BaseField::CHECK_BOX;
    toFill->fields.push_back(field10);
    /*  */ 
    BoolField* field11 = new BoolField
        (
          BitSelectorParameters::BIT_10_ID,
          offsetof(BitSelectorParameters, mBit10),
          true,
          "bit 10",
          "bit 10",
          "bit 10"
        );
    field11->widgetHint=BaseField::CHECK_BOX;
    toFill->fields.push_back(field11);
    /*  */ 
    BoolField* field12 = new BoolField
        (
          BitSelectorParameters::BIT_11_ID,
          offsetof(BitSelectorParameters, mBit11),
          true,
          "bit 11",
          "bit 11",
          "bit 11"
        );
    field12->widgetHint=BaseField::CHECK_BOX;
    toFill->fields.push_back(field12);
    /*  */ 
    BoolField* field13 = new BoolField
        (
          BitSelectorParameters::BIT_12_ID,
          offsetof(BitSelectorParameters, mBit12),
          true,
          "bit 12",
          "bit 12",
          "bit 12"
        );
    field13->widgetHint=BaseField::CHECK_BOX;
    toFill->fields.push_back(field13);
    /*  */ 
    BoolField* field14 = new BoolField
        (
          BitSelectorParameters::BIT_13_ID,
          offsetof(BitSelectorParameters, mBit13),
          true,
          "bit 13",
          "bit 13",
          "bit 13"
        );
    field14->widgetHint=BaseField::CHECK_BOX;
    toFill->fields.push_back(field14);
    /*  */ 
    BoolField* field15 = new BoolField
        (
          BitSelectorParameters::BIT_14_ID,
          offsetof(BitSelectorParameters, mBit14),
          true,
          "bit 14",
          "bit 14",
          "bit 14"
        );
    field15->widgetHint=BaseField::CHECK_BOX;
    toFill->fields.push_back(field15);
    /*  */ 
    BoolField* field16 = new BoolField
        (
          BitSelectorParameters::BIT_15_ID,
          offsetof(BitSelectorParameters, mBit15),
          true,
          "bit 15",
          "bit 15",
          "bit 15"
        );
    field16->widgetHint=BaseField::CHECK_BOX;
    toFill->fields.push_back(field16);
    /*  */ 
    ReflectionDirectory &directory = *ReflectionDirectoryHolder::getReflectionDirectory();
    directory[std::string("Bit Selector Parameters")]= toFill;
   return 0;
}
int BitSelectorParameters::relinkCompositeFields()
{
   return 0;
}

SUPPRESS_OFFSET_WARNING_END


