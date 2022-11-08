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
private:
    FieldGroup *mFieldGroups;

public:
    void setup()
    {
        NumericField field0 = NumericField(0, "field0", 0.0, 25.0, 1.0);
        NumericField field1 = NumericField(1, "field1", 0.0, 25.0, 1.0);
        NumericField field2 = NumericField(2, "field2", 0.0, 25.0, 1.0);
        TextField field3 = TextField(3, "field3", "23 deg C");
        MultipleChoiceField field4 = MultipleChoiceField(4, "field4", 4, "OFF", "ANIMACIJA 1", "ANIMACIJA 2", "ANIMACIJA 3");
        ButtonField field5 = ButtonField(5, "field5", false);
        RGBField field6 = RGBField(6, "field6", 0, 0, 0);

        BasicField f1[] = {field0, field1, field2, field3, field4, field5, field6};
        FieldGroup fieldGroup1(0, "group1", f1, 7);

        NumericField field10 = NumericField(0, "field0", 0.0, 25.0, 1.0);
        NumericField field11 = NumericField(1, "field1", 0.0, 25.0, 1.0);
        NumericField field12 = NumericField(2, "field2", 0.0, 25.0, 1.0);
        TextField field13 = TextField(3, "field3", "23 deg C");
        MultipleChoiceField field14 = MultipleChoiceField(4, "field4", 4, "OFF", "ANIMACIJA 1", "ANIMACIJA 2", "ANIMACIJA 3");
        ButtonField field15 = ButtonField(5, "field5", false);
        RGBField field16 = RGBField(6, "field6", 0, 0, 0);

        BasicField f2[] = {field10, field11, field12, field13, field14, field15, field16};
        FieldGroup fieldGroup2(0, "group1", f2, 7);
    }
};

#endif