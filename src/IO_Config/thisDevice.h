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

#define Npixels 4
Adafruit_NeoPixel pixels(Npixels, 12, NEO_GRB + NEO_KHZ800);

void svjetlinaUpdate(double value){
    int brightness = (int) ((pow(1.12,value) - 1)*15.8);
    
    for(int i = 0; i<Npixels; i++) {
        pixels.setPixelColor(i, pixels.Color(brightness,brightness,brightness));
    }
    pixels.show();
}

void selectColor(int value){
    for(int i=0; i<Npixels; i++){
        switch(value){
            case 0: 
                pixels.setPixelColor(i, pixels.Color(0,0,0));
            break;
            case 1: 
                pixels.setPixelColor(i, pixels.Color(255,0,0));
            break;
            case 2: 
                pixels.setPixelColor(i, pixels.Color(0,255,0));
            break;
            case 3: 
                pixels.setPixelColor(i, pixels.Color(0,0,255));
            break;
            case 4: 
                pixels.setPixelColor(i, pixels.Color(255,255,255));
            break;
        }
    }
    pixels.show();
}

void selectRGB(int r, int g, int b){
    // r = (int)pow(1.0235,r)-1;
    // g = (int)pow(1.0235,g)-1;
    // b = (int)pow(1.0235,b)-1;
    for(int i = 0; i<Npixels; i++){
        pixels.setPixelColor(i, pixels.Color(r,g,b));
    }
    pixels.show();
}

void selectRGB1(int r, int g, int b)
{
    pixels.setPixelColor(0, pixels.Color(r,g,b));
    pixels.show();
}

void selectRGB2(int r, int g, int b)
{
    pixels.setPixelColor(1, pixels.Color(r,g,b));
    pixels.show();
}

void selectRGB3(int r, int g, int b)
{
    pixels.setPixelColor(2, pixels.Color(r,g,b));
    pixels.show();
}

void selectRGB4(int r, int g, int b)
{
    pixels.setPixelColor(3, pixels.Color(r,g,b));
    pixels.show();
}

void changeState(){
    Serial.println("Changed state");
}


class ThisDevice : protected FieldGroups, protected ComplexGroups
{
private:
    NumericField *brightnessField = 
        new NumericField(0, "Svjetlina", INPUT_FIELD, 0.0, 25.0, 1, "", "", svjetlinaUpdate);

    ComplexGroupState *brightnessState = new ComplexGroupState(0, "Svjetlina", 1, brightnessField);

    MultipleChoiceField *colorSelectField =
        new MultipleChoiceField(1, "Boje", INPUT_FIELD, selectColor, 5, "Off", "Red", "Green", "Blue", "White");

    ComplexGroupState *colorSelectState = new ComplexGroupState(1, "Boje", 1, colorSelectField);
    
    RGBField *rgbField =
        new RGBField(2, "Kod boje", 0, 0, 0, selectRGB);
    
    ComplexGroupState *rgbState = new ComplexGroupState(2, "Kod boje", 1, rgbField);

    RGBField *rgbField1 =
        new RGBField(3, "LED 1", 0, 0, 0, selectRGB1);

    RGBField *rgbField2 =
        new RGBField(4, "LED 2", 0, 0, 0, selectRGB2);
        
    RGBField *rgbField3 =
        new RGBField(5, "LED 3", 0, 0, 0, selectRGB3);

    RGBField *rgbField4 =
        new RGBField(6, "LED 4", 0, 0, 0, selectRGB4);
        
    ComplexGroupState *inidividualRgbState = new ComplexGroupState(3, "Individualni RGB", 4, rgbField1, rgbField2, rgbField3, rgbField4);

    ComplexGroup *complexGroup = new ComplexGroup(0, "NOVA GRUPA", changeState, 4, brightnessState, colorSelectState, rgbState, inidividualRgbState);

public:
    void setupFields()
    {
        createGroups(0);
       
        pixels.begin();
        
        createComplexGroups(1, complexGroup);
    }

    void loop(){
 
    }

    virtual double getNumericFieldValue(int groupId, int fieldId) = 0;
    virtual String getTextFieldValue(int groupId, int fieldId) = 0;
    virtual bool getButtonFieldValue(int groupId, int fieldId) = 0;
    virtual int getMCFieldValue(int groupId, int fieldId) = 0;
    virtual RGB getRGBFieldValue(int groupId, int fieldId) = 0;

    virtual void setNumericField(int groupId, int fieldId, double value) = 0;
    virtual void setButtonField(int groupId, int fieldId, bool value) = 0;
    virtual void setMCfield(int groupId, int fieldId, int value) = 0;
    virtual void setRGBfield(int groupId, int fieldId, int R, int G, int B) = 0;
    virtual void setTextField(int groupId, int fieldId, String value) = 0;

    virtual double getNumericFieldInComplexGroupValue(int groupId, int stateId, int fieldId) = 0;
    virtual String getTextFieldValueInComplexGroupValue(int groupId, int stateId, int fieldId) = 0;
    virtual bool getButtonFieldValueInComplexGroupValue(int groupId, int stateId, int fieldId) = 0;
    virtual int getMCFieldValueInComplexGroupValue(int groupId, int stateId, int fieldId) = 0;
    virtual RGB getRGBFieldValueInComplexGroupValue(int groupId, int stateId, int fieldId) = 0;

    virtual void setNumericFieldInComplexGroupValue(int groupId, int stateId, int fieldId, double value) = 0;
    virtual void setButtonFieldInComplexGroupValue(int groupId, int stateId, int fieldId, bool value) = 0;
    virtual void setMCfieldInComplexGroupValue(int groupId, int stateId, int fieldId, int value) = 0;
    virtual void setRGBfieldInComplexGroupValue(int groupId, int stateId, int fieldId, int R, int G, int B) = 0;
    virtual void setTextFieldInComplexGroupValue(int groupId, int stateId, int fieldId, String value) = 0;

    virtual void setComplexGroupState(int groupId, int stateId) = 0;
};

#endif