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
#include <OneWire.h>
#include <DallasTemperature.h>


const double nonLinearBrightnessFunctionBase = 1.16;

int getNonLinearBrightness(int state){
    return int(255/(pow(nonLinearBrightnessFunctionBase, 25) - 1) * (pow(nonLinearBrightnessFunctionBase, state) - 1));
}

int Rpin = 33, Rchannel = 0;
int Gpin = 32, Gchannel = 1;
int Bpin = 25, Bchannel = 2;
int Wpin = 27, Wchannel = 3;

boolean newGaussianValueForSmartStrip = true;

void changeSmartStripState(){

}

void smartStrip_totalBrightness(double value){

}

void smartStrip_controlRed(double value){

}

void smartStrip_controlGreen(double value){

}

void smartStrip_controlBlue(double value){

}

void smartStrip_controlWhite(double value){

}

void smartStrip_setColorCode(int r, int g, int b){

}

void gauss_average(double data){
    newGaussianValueForSmartStrip = true;
}

void gauss_sigma(double data){
    newGaussianValueForSmartStrip = true;
}

void gauss_max(double data){
    newGaussianValueForSmartStrip = true;
}

void gauss_color(int data){
    newGaussianValueForSmartStrip = true;
}

// ---------------------------------------------------

void changeRGBStripState(){

}

void totalBrightness(double value){
    int pwmState = getNonLinearBrightness(value);
    Serial.print("state: ");
    Serial.println(pwmState);
    Serial.print("state: ");
    Serial.println(pwmState);
    Serial.print("state: ");
    Serial.println(pwmState);
    Serial.print("state: ");
    Serial.println(pwmState);
    ledcWrite(Rchannel, pwmState);
    ledcWrite(Gchannel, pwmState);
    ledcWrite(Bchannel, pwmState);
    ledcWrite(Wchannel, pwmState);
}

void controlRed(double value){
    int pwmState = getNonLinearBrightness(value);
    ledcWrite(Rchannel, pwmState);
}

void controlGreen(double value){
       int pwmState = getNonLinearBrightness(value);
    ledcWrite(Gchannel, pwmState);
}

void controlBlue(double value){
    int pwmState = getNonLinearBrightness(value);
    ledcWrite(Bchannel, pwmState);
}

void controlWhite(double value){
    int pwmState = getNonLinearBrightness(value);
    ledcWrite(Wchannel, pwmState);
}

void setColorCode(int r, int g, int b){
    ledcWrite(Rchannel, r);
    ledcWrite(Gchannel, g);
    ledcWrite(Bchannel, b);

    int minimum = r;
    if(minimum > g) minimum = g;
    if(minimum > b) minimum = b;

    ledcWrite(Wchannel, minimum);
}

class ThisDevice : protected FieldGroups, protected ComplexGroups
{
private:

    NumericField *smartStripBrightnessField = 
        new NumericField(0, "Svjetlina", INPUT_FIELD, 0.0, 25.0, 1.0, "", "",  totalBrightness);

    ComplexGroupState *smartStripBrightnessState = 
        new ComplexGroupState(0, "Svjetlina", 1, smartStripBrightnessField);



    NumericField *smartStripRedBrightnessField = 
        new NumericField(0, "Crvena", INPUT_FIELD, 0.0, 25.0, 1.0, "", "",  controlRed);

    NumericField *smartStripGreenBrightnessField = 
        new NumericField(1, "Zelena", INPUT_FIELD, 0.0, 25.0, 1.0, "", "",  controlGreen);

    NumericField *smartStripBlueBrightnessField = 
        new NumericField(2, "Plava", INPUT_FIELD, 0.0, 25.0, 1.0, "", "",  controlBlue);

    ComplexGroupState *smartStripRGBBrightnessState = 
        new ComplexGroupState(1, "Svjetlina - RGB", 3, smartStripRedBrightnessField, smartStripGreenBrightnessField, smartStripBlueBrightnessField);

    
    RGBField *smartStripRGBField = 
        new RGBField(0, "Color code", 0.0, 0.0, 0.0, setColorCode);

    ComplexGroupState *smartStripColorCodeState = 
        new ComplexGroupState(2, "Color code", 1, smartStripRGBField);

    
    NumericField *gaussAverageField = 
        new NumericField(0, "Srednja vrijednost", INPUT_FIELD, 0.0, 180.0, 1.0, "", "", gauss_average);

    NumericField *gaussSigmaField = 
        new NumericField(1, "Odstupanje", INPUT_FIELD, 0.0, 50.0, 1.0, "","", gauss_sigma);

    NumericField *gaussMaxValueField = 
        new NumericField(2, "Maksimalna vrijednost", INPUT_FIELD, 0.0, 25.0, 1.0, "","", gauss_max);

    MultipleChoiceField *gaussColorField = 
        new MultipleChoiceField(3, "Boja", INPUT_FIELD, gauss_color, 4, "Crvena", "Zelena", "Plava", "Bijela");

    ComplexGroupState *gaussState = 
        new ComplexGroupState(3, "Gausova funkcija", 4, gaussAverageField, gaussSigmaField, gaussMaxValueField, gaussColorField);

    ComplexGroup *smartRGBstrip = 
        new ComplexGroup(0, "LED traka - strop", changeSmartStripState, 4, smartStripBrightnessState, smartStripRGBBrightnessState, smartStripColorCodeState, gaussState);

    // ------------------------------------------------------------------------------------------

    NumericField *RGBStripBrightnessField = 
        new NumericField(0, "Svjetlina", INPUT_FIELD, 0.0, 25.0, 1.0, "", "",  totalBrightness);

    ComplexGroupState *RGBStripBrightnessState = 
        new ComplexGroupState(0, "Svjetlina", 1, RGBStripBrightnessField);



    NumericField *RGBStripRedBrightnessField = 
        new NumericField(0, "Crvena", INPUT_FIELD, 0.0, 25.0, 1.0, "", "",  controlRed);

    NumericField *RGBStripGreenBrightnessField = 
        new NumericField(1, "Zelena", INPUT_FIELD, 0.0, 25.0, 1.0, "", "",  controlGreen);

    NumericField *RGBStripBlueBrightnessField = 
        new NumericField(2, "Plava", INPUT_FIELD, 0.0, 25.0, 1.0, "", "",  controlBlue);

    NumericField *RGBStripWhiteBrightnessField = 
        new NumericField(3, "Bijela", INPUT_FIELD, 0.0, 25.0, 1.0, "", "",  controlWhite);

    ComplexGroupState *RGBStripRGBBrightnessState = 
        new ComplexGroupState(1, "Svjetlina - RGB", 4, RGBStripRedBrightnessField, RGBStripGreenBrightnessField, RGBStripBlueBrightnessField, RGBStripWhiteBrightnessField);

    
    RGBField *RGBStripRGBField = 
        new RGBField(0, "Color code", 0.0, 0.0, 0.0, setColorCode);

    ComplexGroupState *RGBStripColorCodeState = 
        new ComplexGroupState(2, "Color code", 1, smartStripRGBField);

    ComplexGroup *RGBstrip = 
        new ComplexGroup(1, "LED traka - iza kauča", changeRGBStripState, 3, RGBStripBrightnessState, RGBStripRGBBrightnessState, RGBStripColorCodeState);

public:
    void setupFields()
    {
        createGroups(0);
       
        ledcSetup(Rchannel, 500, 8);
        ledcAttachPin(Rpin, Rchannel);
        
        ledcSetup(Gchannel, 500, 8);
        ledcAttachPin(Gpin, Gchannel);
        
        ledcSetup(Bchannel, 500, 8);
        ledcAttachPin(Bpin, Bchannel);
   
        ledcSetup(Wchannel, 500, 8);
        ledcAttachPin(Wpin, Wchannel);

        createComplexGroups(2, smartRGBstrip, RGBstrip);

        pinMode(26, OUTPUT);
        digitalWrite(26, HIGH);
    }

    void loop(){
        if(newGaussianValueForSmartStrip){


            newGaussianValueForSmartStrip = false; //obavezno
        }
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