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


void changeSmartStripState(){

}

void totalBrightness(double value){

}

void controlRed(double value){
    Serial.println("setting red to " +  String(value));
//   ledcWrite(1, (int)value);
}

void controlGreen(double value){
    Serial.println("setting green to " +  String(value));
//   ledcWrite(2, (int)value);
}

void controlBlue(double value){
    Serial.println("setting blue to " +  String(value));
//   ledcWrite(3, (int)value);
}

void controlWhite(double value){
    Serial.println("setting white to " +  String(value));
//   ledcWrite(3, (int)value);
}

void setColorCode(int r, int g, int b){

}

void gauss_average(double data){

}

void gauss_sigma(double data){

}

void gauss_max(double data){

}

void gauss_color(int data){

}

void emptyFunction(double data){

}





class ThisDevice : protected FieldGroups, protected ComplexGroups
{
private:

    NumericField *brightnessField = 
        new NumericField(0, "Svjetlina", INPUT_FIELD, 0.0, 25.0, 1.0, "", "",  totalBrightness);

    ComplexGroupState *brightnessState = 
        new ComplexGroupState(0, "Svjetlina", 1, brightnessField);



    NumericField *redBrightnessField = 
        new NumericField(0, "Crvena", INPUT_FIELD, 0.0, 100.0, 1.0, "", "",  controlRed);

    NumericField *greenBrightnessField = 
        new NumericField(1, "Zelena", INPUT_FIELD, 0.0, 100.0, 1.0, "", "",  controlGreen);

    NumericField *blueBrightnessField = 
        new NumericField(2, "Plava", INPUT_FIELD, 0.0, 100.0, 1.0, "", "",  controlBlue);

    ComplexGroupState *RGBBrightnessState = 
        new ComplexGroupState(1, "Svjetlina - RGB", 3, redBrightnessField, greenBrightnessField, blueBrightnessField);

    
    RGBField *rgbField = 
        new RGBField(0, "Color code", 0.0, 0.0, 0.0, setColorCode);

    ComplexGroupState *colorCodeState = 
        new ComplexGroupState(2, "Color code", 1, rgbField);

    
    NumericField *gaussAverageField = 
        new NumericField(0, "Srednja vrijednost", INPUT_FIELD, 0.0, 180.0, 1.0, "", "", gauss_average);

    NumericField *gaussSigmaField = 
        new NumericField(1, "Odstupanje", INPUT_FIELD, 0.0, 50.0, 1.0, "","", gauss_sigma);

    NumericField *gaussMaxValueField = 
        new NumericField(2, "Maksimalna vrijednost", INPUT_FIELD, 0.0, 25.0, 1.0, "","", gauss_max);

    MultipleChoiceField *gaussColorField = 
        new MultipleChoiceField(3, "Boja", INPUT_FIELD, gauss_color, 4, "Crvena", "Zelena", "Plava", "Bijela");

    ComplexGroupState *gauss = 
        new ComplexGroupState(3, "Gausova funkcija", 4, gaussAverageField, gaussSigmaField, gaussMaxValueField, gaussColorField);

    ComplexGroup *smartRGBstrip = 
        new ComplexGroup(0, "LED traka - strop", changeSmartStripState, 4, brightnessState, RGBBrightnessState, colorCodeState, gauss);

public:
    void setupFields()
    {
        createGroups(0);
       
        // ledcAttachPin(25, 1);
        // ledcAttachPin(32, 2);
        // ledcAttachPin(33, 3);
   
        createComplexGroups(1, smartRGBstrip);
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