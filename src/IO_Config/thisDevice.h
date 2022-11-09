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
        int field1_N = 7;
        NumericField *field0 = new NumericField(0, "field0", 0.0, 25.0, 1.0);
        NumericField *field1 = new NumericField(1, "field1", 0.0, 25.0, 1.0);
        NumericField *field2 = new NumericField(2, "field2", 0.0, 25.0, 1.0);
        TextField *field3 = new TextField(3, "field3", "23 deg C");
        MultipleChoiceField *field4 = new MultipleChoiceField(4, "field4", 4, "OFF", "ANIMACIJA 1", "ANIMACIJA 2", "ANIMACIJA 3");
        ButtonField *field5 = new ButtonField(5, "field5", false);
        RGBField *field6 = new RGBField(6, "field6", 0, 0, 0);

        FieldGroup *fieldGroup1 = new FieldGroup(98, "group1", field1_N, field0, field1, field2, field3, field4, field5, field6);

        int field2_N = 7;
        NumericField *field10 = new NumericField(0, "field0", 0.0, 25.0, 1.0);
        NumericField *field11 = new NumericField(1, "field1", 0.0, 25.0, 1.0);
        NumericField *field12 = new NumericField(2, "field2", 0.0, 25.0, 1.0);
        TextField *field13 = new TextField(3, "field3", "23 deg C");
        MultipleChoiceField *field14 = new MultipleChoiceField(4, "field4", 3, "OFF", "ANIMACIJA 1", "ANIMACIJA 2");
        ButtonField *field15 = new ButtonField(5, "field5", false);
        RGBField *field16 = new RGBField(6, "field6", 0, 0, 0);

        FieldGroup *fieldGroup2 = new FieldGroup(99, "group2", field1_N, field10, field11, field12, field13, field14, field15, field16);

        createGroups(2, fieldGroup1, fieldGroup2);
    }

    
};

#endif