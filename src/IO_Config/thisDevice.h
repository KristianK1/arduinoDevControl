#ifndef THIS_DEVICE_H
#define THIS_DEVICE_H

#include "availableFields/numericField.h"
#include "availableFields/textField.h"
#include "availableFields/buttonField.h"
#include "availableFields/RGBField.h"
#include "availableFields/multipleChoiceField.h"
#include "availableFields/basicField.h"
#include "availableFields/FieldGroup.h"

class ThisDevice : protected FieldGroups
{
public:
    void setupFields()
    {
        ///////////////////////////////////////////////
        BasicField *field0 =
            new NumericField(0, "field0", -1.0, 25.0, 1.0);

        BasicField *field1 =
            new NumericField(1, "field1", -1.0, 25.0, 1.0);

        BasicField *field2 =
            new NumericField(2, "field2", -1.0, 25.0, 1.0);

        BasicField *field3 =
            new TextField(3, "field3", "23 deg C");

        BasicField *field4 =
            new MultipleChoiceField(4, "field4", 4, "OFF", "ANIMACIJA 1", "ANIMACIJA 2", "ANIMACIJA 3");

        BasicField *field5 =
            new ButtonField(5, "field5", false);

        BasicField *field6 =
            new RGBField(6, "field6", 0, 0, 0);

        Serial.println("hello0");
        FieldGroup *fieldGroup1 = new FieldGroup(0, "group1", 7, field0, field1, field2, field3, field4, field5, field6);

        BasicField *x = fieldGroup1->getFields()[5];
        ButtonField *fieldAdd = (ButtonField *)x;
        fieldAdd->setValue(true);
        Serial.println(fieldAdd->getId());
        //////////////////////////////////////////////

        BasicField *field10 =
            new NumericField(0, "field0", -1.0, 25.0, 1.0);

        BasicField *field11 =
            new NumericField(1, "field1", -1.0, 25.0, 1.0);

        BasicField *field12 =
            new NumericField(2, "field2", -1.0, 25.0, 1.0);

        BasicField *field13 =
            new TextField(3, "field3", "23 deg C");

        BasicField *field14 =
            new MultipleChoiceField(4, "field4", 3, "OFF", "ANIMACIJA 1", "ANIMACIJA 2");

        BasicField *field15 =
            new ButtonField(5, "field5", false);

        BasicField *field16 =
            new RGBField(6, "field6", 0, 0, 0);
        Serial.println("hello1");
        FieldGroup *fieldGroup2 = new FieldGroup(1, "group2", 7, field10, field11, field12, field13, field14, field15, field16);

        ///////////////////////////////////////////////
        Serial.println("hello2");
        createGroups(2, fieldGroup1, fieldGroup2);
    }

    void group0field0_changed()
    {
        Serial.println("0-0 changed");
    }
};

#endif