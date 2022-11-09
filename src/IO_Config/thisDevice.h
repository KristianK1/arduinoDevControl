#ifndef THIS_DEVICE_H
#define THIS_DEVICE_H

#include "availableFields/numericField.h"
#include "availableFields/textField.h"
#include "availableFields/buttonField.h"
#include "availableFields/RGBField.h"
#include "availableFields/multipleChoiceField.h"
#include "availableFields/basicField.h"
#include "availableFields/FieldGroup.h"

class ThisDevice
{
public:
    FieldGroup **mFieldGroups;
    int NofGroups;

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

        BasicField **f1 = (BasicField **)calloc(field1_N, sizeof(BasicField *));
        f1[0] = field0;
        f1[1] = field1;
        f1[2] = field2;
        f1[3] = field3;
        f1[4] = field4;
        f1[5] = field5;
        f1[6] = field6;
        FieldGroup *fieldGroup1 = new FieldGroup(98, "group1", f1, field1_N);

        int field2_N = 7;
        NumericField *field10 = new NumericField(0, "field0", 0.0, 25.0, 1.0);
        NumericField *field11 = new NumericField(1, "field1", 0.0, 25.0, 1.0);
        NumericField *field12 = new NumericField(2, "field2", 0.0, 25.0, 1.0);
        TextField *field13 = new TextField(3, "field3", "23 deg C");
        MultipleChoiceField *field14 = new MultipleChoiceField(4, "field4", 3, "OFF", "ANIMACIJA 1", "ANIMACIJA 2");
        ButtonField *field15 = new ButtonField(5, "field5", false);
        RGBField *field16 = new RGBField(6, "field6", 0, 0, 0);

        BasicField **f2 = (BasicField **)calloc(field2_N, sizeof(BasicField *));
        f2[0] = field10;
        f2[1] = field11;
        f2[2] = field12;
        f2[3] = field13;
        f2[4] = field14;
        f2[5] = field15;
        f2[6] = field16;
        FieldGroup *fieldGroup2 = new FieldGroup(99, "group2", f2, field2_N);

        NofGroups = 2;
        FieldGroup **groups = (FieldGroup **)calloc(NofGroups, sizeof(FieldGroup *));
        groups[0] = fieldGroup1;
        groups[1] = fieldGroup2;
        mFieldGroups = groups;
    }


    
};

#endif