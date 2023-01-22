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
<<<<<<< Updated upstream

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
=======
#include "ArduinoJson.h"
#include <Adafruit_NeoPixel.h>
#include<math.h>

Adafruit_NeoPixel pixels(3, 13, NEO_GRB + NEO_KHZ800);

void led1_changed(double value){
    int brightness = (int) (pow(1.3,value) - 1)*5.3;
    pixels.begin();
    pixels.setPixelColor(0, pixels.Color(brightness,brightness,brightness));
    pixels.show();
}

void led2_changed(int value){
    pixels.begin();
    switch(value){
        case 0: 
            pixels.setPixelColor(1, pixels.Color(0,0,0));
        break;
        case 1: 
            pixels.setPixelColor(1, pixels.Color(255,0,0));
        break;
        case 2: 
            pixels.setPixelColor(1, pixels.Color(0,255,0));
        break;
        case 3: 
            pixels.setPixelColor(1, pixels.Color(0,0,255));
        break;
        case 4: 
            pixels.setPixelColor(1, pixels.Color(255,255,255));
        break;
    }
    pixels.show();
}

void led3_changed(int r, int g, int b){
    r = (int)pow(1.0235,r)-1;
    g = (int)pow(1.0235,g)-1;
    b = (int)pow(1.0235,b)-1;
    pixels.begin();
    pixels.setPixelColor(2, pixels.Color(r,g,b));
    pixels.show();
}

void led4_changed(bool value)
{
    digitalWrite(23, value);
}

// void RGB_1(int r, int g, int b){
//     r = (int)pow(1.0235,r);
//     g = (int)pow(1.0235,g);
//     b = (int)pow(1.0235,b);
//     pixels.begin();
//     pixels.setPixelColor(2, pixels.Color(r,g,b));
//     pixels.show();
// }



// void ostaloNumeric(double value)
// {
//     Serial.println("ostalo");
// }

// void ostaloMC(int value)
// {
//     Serial.println("ostalo");
// }

// void ostaloRGB(int r, int g, int b){

// }

// void ostalo(){

// }

>>>>>>> Stashed changes

class ThisDevice : protected FieldGroups, protected ComplexGroups
{
public:
    void setupFields()
    {
        ///////////////////////////////////////////////
        BasicField *field0 =
<<<<<<< Updated upstream
            new NumericField(50, "field0", -1.0, 25.0, 1.0, group0field0_changed__H);

        BasicField *field1 =
            new NumericField(1, "field1", -1.0, 25.0, 1.0, group0field0_changed);

        BasicField *field2 =
            new NumericField(2, "field2", -1.0, 25.0, 0.5, group0field0_changed);

        BasicField *field3 =
            new TextField(3, "field3", INPUT_FIELD, "23 deg C", group0field0_changed);

        BasicField *field4 =
            new MultipleChoiceField(4, "field4", INPUT_FIELD, group0field0_changed, 4, "OFF", "ANIMACIJA 1", "ANIMACIJA 2", "ANIMACIJA 3");

        BasicField *field5 =
            new ButtonField(5, "field5", INPUT_FIELD, false, group0field0_changed);

        BasicField *field6 =
            new RGBField(6, "field6", 0, 0, 0, group0field0_changed);

        BasicField *field7 =
            new ButtonField(7, "field7", INPUT_FIELD, true, group0field0_changed);
=======
            new NumericField(0, "LED 1", 0.0, 15.0, 0.5, led1_changed);

        BasicField *field1 =
            new MultipleChoiceField(1, "LED 2", INPUT_FIELD, led2_changed, 5, "Off", "Red", "Green", "Blue", "White");

        BasicField *field2 =
            new RGBField(2, "LED 3", 0, 0, 0, led3_changed);

        FieldGroup *fieldGroup0 =
            new FieldGroup(0, "WS2812b", 3, field0, field1, field2);


>>>>>>> Stashed changes

        BasicField *field8 =
            new ButtonField(8, "field8", INPUT_FIELD, true, group0field0_changed);

        BasicField *field9 =
            new ButtonField(99, "field9", INPUT_FIELD, true, group0field0_changed);

        FieldGroup *fieldGroup1 =
            new FieldGroup(0, "group1_rename", 10, field0, field1, field2, field3, field4, field5, field6, field7, field8, field9);
        //////////////////////////////////////////////
<<<<<<< Updated upstream

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
=======
        BasicField *field3 =
            new ButtonField(1, "Blue LED", INPUT_FIELD, false, led4_changed);

        FieldGroup *fieldGroup1 =
            new FieldGroup(1, "LED", 1, field3);

        createGroups(2, fieldGroup0, fieldGroup1);
>>>>>>> Stashed changes

        //////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////
        /// @brief ///////////////////////////////////////////////////////////////////////////////

<<<<<<< Updated upstream
        BasicField *field21 =
            new NumericField(0, "RField", 0.0, 25.0, 1.0, group0field0_changed);

        BasicField *field22 =
            new NumericField(1, "GField", 0.0, 25.0, 1.0, group0field0_changed);

        BasicField *field23 =
            new NumericField(2, "BField", 0.0, 25.0, 1.0, group0field0_changed);
=======
        // BasicField *field21 =
        //     new NumericField(0, "RField", 0.0, 25.0, 1.0, ostaloNumeric);

        // BasicField *field22 =
        //     new NumericField(1, "GField", 0.0, 25.0, 1.0, ostaloNumeric);

        // BasicField *field23 =
        //     new NumericField(2, "BField", 0.0, 25.0, 1.0, ostaloNumeric);
>>>>>>> Stashed changes

        // ComplexGroupState *state1 =
        //     new ComplexGroupState(0, "individual", 3, field21, field22, field23);

<<<<<<< Updated upstream
        BasicField *fieldRGB =
            new RGBField(0, "RGB", 0, 0, 0, group0field0_changed);
=======
        // BasicField *fieldRGB =
        //     new RGBField(0, "RGB", 0, 0, 0, ostaloRGB);
>>>>>>> Stashed changes

        // ComplexGroupState *state2 =
        //     new ComplexGroupState(1, "rgb", 1, fieldRGB);

<<<<<<< Updated upstream
        BasicField *animationsF =
            new MultipleChoiceField(0, "animations", INPUT_FIELD, group0field0_changed, 6, "OFF", "A1", "A2", "A3", "A4", "A5");
=======
        // BasicField *animationsF =
        //     new MultipleChoiceField(0, "animations", INPUT_FIELD, ostaloMC, 6, "OFF", "A1", "A2", "A3", "A4", "A5");
>>>>>>> Stashed changes

        // ComplexGroupState *state3 =
        //     new ComplexGroupState(2, "animations", 1, animationsF);

<<<<<<< Updated upstream
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
=======
        // ComplexGroup *CG0 =
        //     new ComplexGroup(0, "complexGroup1", ostalo, 3, state1, state2, state3);

        ////////////////////////////////////////////////////////////////////////////////////////////////

        createComplexGroups(0);
>>>>>>> Stashed changes
    }
};

#endif