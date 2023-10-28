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





class ThisDevice : protected FieldGroups, protected ComplexGroups
{
private:

    NumericField *redField = 
        new NumericField(0, "Red", INPUT_FIELD, 0.0, 100.0, 1.0, "", "pst",  controlRed);


    NumericField *greenField = 
        new NumericField(1, "Green", INPUT_FIELD, 0.0, 100.0, 1.0, "", "pst",  controlGreen);


    NumericField *blueField = 
        new NumericField(2, "Blue", INPUT_FIELD, 0.0, 100.0, 1.0, "", "pst",  controlBlue);


    FieldGroup *fg1 = 
    new FieldGroup(0, "RGB", 3, redField, greenField, blueField);


public:
    void setupFields()
    {
        createGroups(1, fg1);
       
        ledcAttachPin(25, 1);
        ledcAttachPin(32, 2);
        ledcAttachPin(33, 3);
   
        createComplexGroups(0);
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