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
#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire1(32);
OneWire oneWire2(33); 

DallasTemperature sensors1(&oneWire1);
DallasTemperature sensors2(&oneWire2);

void emptyFunctionNumericField(double data){

}

void emptyFunctionButtonField(boolean data){

}

void wantedTemperatureChanged(double wantedTemperature){

}


class ThisDevice : protected FieldGroups, protected ComplexGroups
{
private:

    NumericField *roomTemperatureField1 = 
        new NumericField(0, "Room temperature",  OUTPUT_FIELD, 0.0, 150.0, 0.5, "", "°C", emptyFunctionNumericField);

    NumericField *radiatorTemperatureField = 
        new NumericField(1, "Radiator temperature", OUTPUT_FIELD, 0.0, 150.0, 10.0, "", "°C", emptyFunctionNumericField);

    NumericField *targetTemperature = 
        new NumericField(2, "Target temperature", INPUT_FIELD, 10.0, 30.0, 0.5, "", "°C", wantedTemperatureChanged);

    ButtonField *heatingStateField = 
        new ButtonField(3, "Heating state", OUTPUT_FIELD, false, emptyFunctionButtonField);

    FieldGroup *fieldGroup =
        new FieldGroup(0, "Heating system", 4, roomTemperatureField1, radiatorTemperatureField, targetTemperature, heatingStateField);

public:
    void setupFields()
    {
        sensors1.begin();
        sensors2.begin();

        createGroups(1, fieldGroup);        
        createComplexGroups(0);
    }


    void temperatureLoop1(){
        sensors1.begin();
        sensors1.requestTemperatures(); // Send the command to get temperatures
        float tempC = sensors1.getTempCByIndex(0);
        // Serial.println(tempC);

        float currentValue = roomTemperatureField1->getValue();
        // Serial.println(currentValue);

        double newTemp_normalized = int(tempC / roomTemperatureField1->getStep()) * roomTemperatureField1->getStep();

        float diff = currentValue - tempC;
        if(diff < 0){
            diff *= -1;
        }

        if(diff >= roomTemperatureField1->getStep() * 0.75){
            setNumericField(fieldGroup->getGroupId(), roomTemperatureField1->getId(), newTemp_normalized);
        }
    }

    void temperatureLoop2(){
        sensors2.begin();
        sensors2.requestTemperatures(); // Send the command to get temperatures
        float tempC = sensors2.getTempCByIndex(0);
        // Serial.println(tempC);

        float currentValue = radiatorTemperatureField->getValue();
        // Serial.println(currentValue);

        double newTemp_normalized = int(tempC / radiatorTemperatureField->getStep()) * radiatorTemperatureField->getStep();

        float diff = currentValue - tempC;
        if(diff < 0){
            diff *= -1;
        }

        if(diff >= radiatorTemperatureField->getStep() * 0.75){
            setNumericField(fieldGroup->getGroupId(), radiatorTemperatureField->getId(), newTemp_normalized);
        }
    }

    void loop(){
        temperatureLoop1();
        temperatureLoop2();
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