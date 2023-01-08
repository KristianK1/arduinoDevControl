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
            new NumericField(0, "field0", 0.0, 25.0, 0.5, group0field0_changed__H);

        BasicField *field1 =
            new NumericField(1, "field1", 0.0, 25.0, 0.25, group0field0_changed);

        BasicField *field2 =
            new MultipleChoiceField(4, "field4", INPUT_FIELD, group0field0_changed, 4, "OFF", "ANIMACIJA 1", "ANIMACIJA 2", "ANIMACIJA 3");

        BasicField *field3 =
            new ButtonField(5, "field5", INPUT_FIELD, false, group0field0_changed);

        FieldGroup *fieldGroup1 =
            new FieldGroup(0, "group0", 4, field0, field1, field2, field3);

        //////////////////////////////////////////////
        createGroups(1, fieldGroup1);

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
            new MultipleChoiceField(0, "animations", INPUT_FIELD, group0field0_changed, 6, "OFF", "A1", "A2", "A3", "A4", "A5");

        ComplexGroupState *state3 =
            new ComplexGroupState(2, "animations", 1, animationsF);

        ComplexGroup *CG0 =
            new ComplexGroup(0, "complexGroup1", group0field0_changed, 3, state1, state2, state3);

        ////////////////////////////////////////////////////////////////////////////////////////////////

        createComplexGroups(1, CG0);
    }
};

#endif