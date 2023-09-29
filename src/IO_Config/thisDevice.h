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

class ThisDevice : protected FieldGroups, protected ComplexGroups
{
public:
    void setupFields()
    {
        BasicField *field0 =
            new NumericField(0, "LED 1", 0.0, 15.0, 0.5, "T=", "°C", led1_changed);

        BasicField *field1 =
            new MultipleChoiceField(1, "LED 2", INPUT_FIELD, led2_changed, 5, "Off", "Red", "Green", "Blue", "White");

        BasicField *field2 =
            new RGBField(2, "LED 3", 0, 0, 0, led3_changed);

        FieldGroup *fieldGroup0 =
            new FieldGroup(0, "WS2812b", 3, field0, field1, field2);

        BasicField *field3 =
            new ButtonField(1, "Blue LED", INPUT_FIELD, false, led4_changed);

        FieldGroup *fieldGroup1 =
            new FieldGroup(1, "LED", 1, field3);

        createGroups(2, fieldGroup0, fieldGroup1);
       
        createComplexGroups(0);
    }
};

#endif