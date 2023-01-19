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
#include "ArduinoJson.h"
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels(1, 13, NEO_GRB + NEO_KHZ800);


void numeric1_changed(double value){

}


void button1_changed(bool value)
{
    Serial.println("button1_function");
    digitalWrite(23, value);
}

void RGB_1(int r, int g, int b){
    Serial.println(r);
    Serial.println(g);
    Serial.println(b);

    pixels.begin();
    pixels.setPixelColor(0, pixels.Color(r,g,b));
    pixels.show();
    Serial.println("rgb_1_function");
}

void ostaloNumeric(double value)
{
    Serial.println("ostalo");
}

void ostaloMC(int value)
{
    Serial.println("ostalo");
}

void ostaloRGB(int r, int g, int b){

}

void ostalo(){

}

class ThisDevice : protected FieldGroups, protected ComplexGroups
{
public:
    void setupFields()
    {
        ///////////////////////////////////////////////
        BasicField *field0 =
            new NumericField(0, "numeric1", 0.0, 25.0, 0.5, numeric1_changed);

        BasicField *field1 =
            new ButtonField(1, "button1", INPUT_FIELD, false, button1_changed);

        BasicField *field2 =
            new RGBField(2, "RGB", 0, 0, 0, RGB_1);

        FieldGroup *fieldGroup0 =
            new FieldGroup(0, "group0", 3, field0, field1, field2);

        //////////////////////////////////////////////
        createGroups(1, fieldGroup0);

        //////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////
        /// @brief ///////////////////////////////////////////////////////////////////////////////

        BasicField *field21 =
            new NumericField(0, "RField", 0.0, 25.0, 1.0, ostaloNumeric);

        BasicField *field22 =
            new NumericField(1, "GField", 0.0, 25.0, 1.0, ostaloNumeric);

        BasicField *field23 =
            new NumericField(2, "BField", 0.0, 25.0, 1.0, ostaloNumeric);

        ComplexGroupState *state1 =
            new ComplexGroupState(0, "individual", 3, field21, field22, field23);

        BasicField *fieldRGB =
            new RGBField(0, "RGB", 0, 0, 0, ostaloRGB);

        ComplexGroupState *state2 =
            new ComplexGroupState(1, "rgb", 1, fieldRGB);

        BasicField *animationsF =
            new MultipleChoiceField(0, "animations", INPUT_FIELD, ostaloMC, 6, "OFF", "A1", "A2", "A3", "A4", "A5");

        ComplexGroupState *state3 =
            new ComplexGroupState(2, "animations", 1, animationsF);

        ComplexGroup *CG0 =
            new ComplexGroup(0, "complexGroup1", ostalo, 3, state1, state2, state3);

        ////////////////////////////////////////////////////////////////////////////////////////////////

        createComplexGroups(1, CG0);
    }
};

#endif