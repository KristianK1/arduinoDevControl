#ifndef THIS_DEVICE_H
#define THIS_DEVICE_H

#include "availableFields/numericField.h"
#include "availableFields/textField.h"
#include "availableFields/buttonField.h"
#include "availableFields/RGBField.h"
#include "availableFields/multipleChoiceField.h"

class ThisDevice
{
    NumericField field0 = NumericField(0, "field0", 0.0, 25.0, 1.0);
    NumericField field1 = NumericField(1, "field1", 0.0, 25.0, 1.0);
    NumericField field2 = NumericField(2, "field2", 0.0, 25.0, 1.0);

    TextField field3 = TextField(3, "field3", "23 deg C");

    MultipleChoiceField field4 = MultipleChoiceField(4, "field4", 4, "OFF", "ANIMACIJA 1", "ANIMACIJA 2", "ANIMACIJA 3");

    ButtonField field5 = ButtonField(5, "field5", false);

    RGBField field6 = RGBField(6, "field6", 0, 0, 0);
};

#endif