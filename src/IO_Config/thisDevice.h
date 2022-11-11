#ifndef THIS_DEVICE_H
#define THIS_DEVICE_H

#include "availableFields/numericField.h"
#include "availableFields/textField.h"
#include "availableFields/buttonField.h"
#include "availableFields/RGBField.h"
#include "availableFields/multipleChoiceField.h"
#include "availableFields/basicField.h"
#include "availableFields/FieldGroup.h"
#include "availableFields/ComplexGroup.h"

void group0field0_changed()
{
    Serial.println("0-0 changed");
}

void group0field0_changed__H()
{
    Serial.println("0-0 changed ___H");
}

void RGBchanged()
{
    Serial.println("changeddddddddddd - func pointer works");
}

class ThisDevice : protected FieldGroups, protected ComplexGroups
{
public:
    void setupFields()
    {
        ///////////////////////////////////////////////
        BasicField *field0 =
            new NumericField(0, "field0", -1.0, 25.0, 1.0, group0field0_changed__H);

        BasicField *field1 =
            new NumericField(1, "field1", -1.0, 25.0, 1.0, group0field0_changed);

        BasicField *field2 =
            new NumericField(2, "field2", -1.0, 25.0, 1.0, group0field0_changed);

        BasicField *field3 =
            new TextField(3, "field3", INPUT_FIELD, "23 deg C", group0field0_changed);

        BasicField *field4 =
            new MultipleChoiceField(4, "field4", INPUT_FIELD, group0field0_changed, 4, "OFF", "ANIMACIJA 1", "ANIMACIJA 2", "ANIMACIJA 3");

        BasicField *field5 =
            new ButtonField(5, "field5", INPUT_FIELD, false, group0field0_changed);

        BasicField *field6 =
            new RGBField(6, "field6", 0, 0, 0, group0field0_changed);

        FieldGroup *fieldGroup1 =
            new FieldGroup(0, "group1", 7, field0, field1, field2, field3, field4, field5, field6);
        //////////////////////////////////////////////

        BasicField *field10 =
            new NumericField(0, "field0", -1.0, 25.0, 1.0, group0field0_changed);

        BasicField *field11 =
            new NumericField(1, "field1", -1.0, 25.0, 1.0, group0field0_changed);

        BasicField *field12 =
            new NumericField(2, "field2", -1.0, 25.0, 1.0, group0field0_changed);

        BasicField *field13 =
            new TextField(3, "field3", INPUT_FIELD, "23 deg C", group0field0_changed);

        BasicField *field14 =
            new MultipleChoiceField(4, "field4", INPUT_FIELD, group0field0_changed, 3, "OFF", "ANIMACIJA 1", "ANIMACIJA 2");

        BasicField *field15 =
            new ButtonField(5, "field5", INPUT_FIELD, false, group0field0_changed);

        BasicField *field16 =
            new RGBField(6, "field6", 0, 0, 0, group0field0_changed);

        FieldGroup *fieldGroup2 = new FieldGroup(1, "group2", 7, field10, field11, field12, field13, field14, field15, field16);

        ///////////////////////////////////////////////

        createGroups(2, fieldGroup1, fieldGroup2);

        //////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////
        /// @brief ///////////////////////////////////////////////////////////////////////////////

        BasicField *field21 =
            new NumericField(0, "RField", 0.0, 25.0, 1.0, group0field0_changed);

        BasicField *field22 =
            new NumericField(1, "GField", 0.0, 25.0, 1.0, group0field0_changed);

        BasicField *field23 =
            new NumericField(2, "BField", 0.0, 25.0, 1.0, group0field0_changed);

        ComplexGroupState *state1 =
            new ComplexGroupState(0, "individual", 3, field21, field22, field23);

        BasicField *fieldRGB =
            new RGBField(0, "RGB", 0, 0, 0, group0field0_changed);

        ComplexGroupState *state2 =
            new ComplexGroupState(1, "rgb", 1, fieldRGB);

        BasicField *animationsF =
            new MultipleChoiceField(0, "animations", INPUT_FIELD, group0field0_changed, 5, "OFF", "A1", "A2", "A3", "A4");

        ComplexGroupState *state3 =
            new ComplexGroupState(2, "animations", 1, animationsF);

        ComplexGroup *group1 =
            new ComplexGroup(0, "complexGroup1", group0field0_changed, 3, state1, state2, state3);

        ////////////////////////////////////////////////////////////////////////////////////////////////

        BasicField *field21_x =
            new NumericField(0, "RField", 0.0, 25.0, 1.0, group0field0_changed);

        BasicField *field22_x =
            new NumericField(1, "GField", 0.0, 25.0, 1.0, group0field0_changed);

        BasicField *field23_x =
            new NumericField(2, "BField", 0.0, 25.0, 1.0, group0field0_changed);

        ComplexGroupState *state1_x =
            new ComplexGroupState(0, "individual", 3, field21_x, field22_x, field23_x);
        ////////////////////
        BasicField *fieldRGB_x =
            new RGBField(0, "RGB", 0, 0, 0, RGBchanged);

        ComplexGroupState *state2_x =
            new ComplexGroupState(1, "rgb", 1, fieldRGB_x);
        ////////////////////
        BasicField *animationsF_x =
            new MultipleChoiceField(0, "animations", INPUT_FIELD, group0field0_changed, 5, "OFF", "A1", "A2", "A3", "A4");

        ComplexGroupState *state3_x =
            new ComplexGroupState(2, "animations", 1, animationsF_x);
        ///////////////////
        ComplexGroup *group2 =
            new ComplexGroup(1, "complexGroup1_new", group0field0_changed, 3, state1_x, state2_x, state3_x);

        createComplexGroups(2, group1, group2);
    }
};

#endif