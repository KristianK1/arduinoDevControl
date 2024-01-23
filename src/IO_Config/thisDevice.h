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
#include <math.h>

#define eulerNumber 2.718281828459045

const double nonLinearBrightnessFunctionBase = 1.16;

int getNonLinearBrightness(int state){
    return int(255/(pow(nonLinearBrightnessFunctionBase, 25) - 1) * (pow(nonLinearBrightnessFunctionBase, state) - 1));
}

int Rpin = 33, Rchannel = 0;
int Gpin = 25, Gchannel = 1;
int Bpin = 32, Bchannel = 2;
int Wpin = 27, Wchannel = 3;

#define LED_PIN 5

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 180

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

boolean newIndividualValueForSmartStrip = true;
boolean newGaussianValueForSmartStrip = true;




void changeSmartStripState(){

}

void smartStrip_totalBrightness(double value){
    int pwmState = getNonLinearBrightness(value);
    for(int i = 0; i< LED_COUNT; i++){
        strip.setPixelColor(i, strip.Color(pwmState, pwmState, pwmState));  
    }
    strip.show();
}

void smartStrip_controlRed(double value){
    newIndividualValueForSmartStrip = true;
}

void smartStrip_controlGreen(double value){
    newIndividualValueForSmartStrip = true;
}

void smartStrip_controlBlue(double value){
    newIndividualValueForSmartStrip = true;
}

void smartStrip_setColorCode(int r, int g, int b){
    if(r == 256) r = 255;
    if(g == 256) g = 255;
    if(b == 256) b = 255;
    
    for(int i = 0; i< LED_COUNT; i++){
        strip.setPixelColor(i, strip.Color(r, g, b));  
    }
    strip.show();
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
        new NumericField(0, "Svjetlina", INPUT_FIELD, 0.0, 25.0, 1.0, "", "",  smartStrip_totalBrightness);

    ComplexGroupState *smartStripBrightnessState = 
        new ComplexGroupState(0, "Svjetlina", 1, smartStripBrightnessField);



    NumericField *smartStripRedBrightnessField = 
        new NumericField(0, "Crvena", INPUT_FIELD, 0.0, 25.0, 1.0, "", "",  smartStrip_controlRed);

    NumericField *smartStripGreenBrightnessField = 
        new NumericField(1, "Zelena", INPUT_FIELD, 0.0, 25.0, 1.0, "", "",  smartStrip_controlGreen);

    NumericField *smartStripBlueBrightnessField = 
        new NumericField(2, "Plava", INPUT_FIELD, 0.0, 25.0, 1.0, "", "",  smartStrip_controlBlue);

    ComplexGroupState *smartStripRGBBrightnessState = 
        new ComplexGroupState(1, "Svjetlina - RGB", 3, smartStripRedBrightnessField, smartStripGreenBrightnessField, smartStripBlueBrightnessField);

    
    RGBField *smartStripRGBField = 
        new RGBField(0, "Color code", 0.0, 0.0, 0.0, smartStrip_setColorCode);

    ComplexGroupState *smartStripColorCodeState = 
        new ComplexGroupState(2, "Color code", 1, smartStripRGBField);

    
    NumericField *gaussAverageField = 
        new NumericField(0, "Srednja vrijednost", INPUT_FIELD, 0.0, 179.0, 1.0, "", "", gauss_average);

    NumericField *gaussSigmaField = 
        new NumericField(1, "Odstupanje", INPUT_FIELD, 0.0, 50.0, 1.0, "","", gauss_sigma);

    NumericField *gaussMaxValueField = 
        new NumericField(2, "Maksimalna vrijednost", INPUT_FIELD, 0.0, 255.0, 1.0, "","", gauss_max);

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
        new ComplexGroupState(2, "Color code", 1, RGBStripRGBField);

    ComplexGroup *RGBstrip = 
        new ComplexGroup(1, "LED traka - iza kauča", changeRGBStripState, 3, RGBStripBrightnessState, RGBStripRGBBrightnessState, RGBStripColorCodeState);

public:
    void setupFields()
    {
        createGroups(0);
       
        strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
        strip.show();     

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
        if(newIndividualValueForSmartStrip){
            int red = smartStripRedBrightnessField->getValue();
            int green = smartStripGreenBrightnessField->getValue();
            int blue = smartStripBlueBrightnessField->getValue();
            
            red = getNonLinearBrightness(red);
            green = getNonLinearBrightness(green);
            blue = getNonLinearBrightness(blue);

            for(int i = 0; i< LED_COUNT; i++){
                strip.setPixelColor(i, strip.Color(red, green, blue));  
            }
            strip.show();

            newIndividualValueForSmartStrip = false;
        }



        if(newGaussianValueForSmartStrip){
            double average = gaussAverageField->getValue();
            double sigma = gaussSigmaField->getValue();
            double maksimum = gaussMaxValueField->getValue();
            int color = gaussColorField->getValue();

            Serial.println("gausian values: ");
            Serial.println(average);
            Serial.println(sigma);
            Serial.println(maksimum);
            
            switch(color){
                    case 0: //red
                        for(int i = 0; i< LED_COUNT; i++){
                            int value = int(maksimum * pow(EULER, -1.0/2 * pow(i-average,2)/pow(sigma,2)));
                            strip.setPixelColor(i, strip.Color(value, 0, 0));
                        }
                        strip.show();
                    break;
                    case 1: //green
                        for(int i = 0; i< LED_COUNT; i++){
                            int value = int(maksimum * pow(EULER, -1.0/2 * pow(i-average,2)/pow(sigma,2)));
                            strip.setPixelColor(i, strip.Color(0, value, 0));
                        }
                        strip.show();
                    break;
                    case 2: //blue
                        for(int i = 0; i< LED_COUNT; i++){
                            int value = int(maksimum * pow(EULER, -1.0/2 * pow(i-average,2)/pow(sigma,2)));
                            strip.setPixelColor(i, strip.Color(0, 0, value));
                        }
                        strip.show();
                    break;
                    case 3: //white
                        for(int i = 0; i< LED_COUNT; i++){
                            int value = int(maksimum * pow(EULER, -1.0/2 * pow(i-average,2)/pow(sigma,2)));
                            strip.setPixelColor(i, strip.Color(value, value, value));
                        }
                        strip.show();
                    break;  
            }

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