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

OneWire oneWire1(25);
OneWire oneWire2(26);
OneWire oneWire3(27);
OneWire oneWire4(32);

int heatingRelayPin = 33;

DallasTemperature sensors1(&oneWire1);
DallasTemperature sensors2(&oneWire2);
DallasTemperature sensors3(&oneWire3);
DallasTemperature sensors4(&oneWire4);

bool newTargetTemperatureFlag = true;

void emptyFunctionNumericField(double data){

}

void emptyFunctionMCField(int data){

}

void emptyFunctionButtonField(boolean data){

}

void wantedTemperatureChanged(double wantedTemperature){
    
}


class ThisDevice : protected FieldGroups, protected ComplexGroups
{
private:

    NumericField *temp1 = 
        new NumericField(0, "Soba1",  OUTPUT_FIELD, -20.0, 80.0, 0.5, "", "°C", emptyFunctionNumericField);

    NumericField *temp2 = 
        new NumericField(1, "Dnevna soba", OUTPUT_FIELD, -20.0, 80.0, 0.5, "", "°C", emptyFunctionNumericField);

    NumericField *temp3 = 
        new NumericField(2, "Soba2",  OUTPUT_FIELD, -20.0, 80.0, 0.5, "", "°C", emptyFunctionNumericField);

    NumericField *temp4 = 
        new NumericField(3, "Vanjska", OUTPUT_FIELD, -20.0, 80.0, 0.5, "", "°C", emptyFunctionNumericField);
       
    MultipleChoiceField *heatingType = 
        new MultipleChoiceField(4, "Heating type", INPUT_FIELD, emptyFunctionMCField, 4, "Minimum", "Srednji", "Maksimum", "Srednja vrijednost");

    NumericField *targetTemperature = 
        new NumericField(5, "Target temperature", INPUT_FIELD, 10.0, 30.0, 0.5, "", "°C", wantedTemperatureChanged);

    ButtonField *heatingStateField = 
        new ButtonField(6, "Heating state", OUTPUT_FIELD, false, emptyFunctionButtonField);

    FieldGroup *fieldGroup =
        new FieldGroup(0, "Heating system", 7, temp1, temp2, temp3, temp4, heatingType, targetTemperature, heatingStateField);

    boolean heatingRelayState = false;
    double heatingRelayStateTimer = 0;

public:
    void setupFields()
    {
        sensors1.begin();
        sensors2.begin();
        sensors3.begin();
        sensors4.begin();
        pinMode(33, OUTPUT);
        pinMode(34, INPUT_PULLUP);
        pinMode(35, INPUT_PULLUP);
        

        createGroups(1, fieldGroup);        
        createComplexGroups(0);
    }


    void temperatureLoop1(){
        sensors1.begin();
        sensors1.requestTemperatures(); // Send the command to get temperatures
        float tempC = sensors1.getTempCByIndex(0);
        // Serial.println(tempC);

        float currentValue = temp1->getValue();
        // Serial.println(currentValue);

        double newTemp_normalized = int(tempC / temp1->getStep()) * temp1->getStep();

        float diff = currentValue - tempC;
        if(diff < 0){
            diff *= -1;
        }

        if(diff >= temp1->getStep() * 1){
            setNumericField(fieldGroup->getGroupId(), temp1->getId(), newTemp_normalized);
        }
    }

    void temperatureLoop2(){
        sensors2.begin();
        sensors2.requestTemperatures(); // Send the command to get temperatures
        float tempC = sensors2.getTempCByIndex(0);
        // Serial.println(tempC);

        float currentValue = temp2->getValue();
        // Serial.println(currentValue);

        double newTemp_normalized = int(tempC / temp2->getStep()) * temp2->getStep();

        float diff = currentValue - tempC;
        if(diff < 0){
            diff *= -1;
        }

        if(diff >= temp2->getStep() * 1.2){
            setNumericField(fieldGroup->getGroupId(), temp2->getId(), newTemp_normalized);
        }
    }

    void temperatureLoop3(){
        sensors3.begin();
        sensors3.requestTemperatures(); // Send the command to get temperatures
        float tempC = sensors3.getTempCByIndex(0);
        // Serial.println(tempC);

        float currentValue = temp3->getValue();
        // Serial.println(currentValue);

        double newTemp_normalized = int(tempC / temp3->getStep()) * temp3->getStep();

        float diff = currentValue - tempC;
        if(diff < 0){
            diff *= -1;
        }

        if(diff >= temp3->getStep() * 1.2){
            setNumericField(fieldGroup->getGroupId(), temp3->getId(), newTemp_normalized);
        }
    }
    
    void temperatureLoop4(){
        sensors4.begin();
        sensors4.requestTemperatures(); // Send the command to get temperatures
        float tempC = sensors4.getTempCByIndex(0);
        // Serial.println(tempC);

        float currentValue = temp4->getValue();
        // Serial.println(currentValue);

        double newTemp_normalized = int(tempC / temp4->getStep()) * temp4->getStep();

        float diff = currentValue - tempC;
        if(diff < 0){
            diff *= -1;
        }

        if(diff >= temp4->getStep() * 1.2){
            setNumericField(fieldGroup->getGroupId(), temp4->getId(), newTemp_normalized);
        }
    }

    void wantedTemperatureLoop(){
        double temp1Value = temp1->getValue();
        double temp2Value = temp2->getValue();
        double temp3Value = temp3->getValue();
        
        Serial.println("Temperature values: ");
        Serial.println(temp1Value);
        Serial.println(temp2Value);
        Serial.println(temp3Value);
        
        double wantedTemperature = targetTemperature->getValue();

        double valueToCompare;

        switch (heatingType->getValue()){
            case 0: //minimum
                valueToCompare = temp1Value;
                if(valueToCompare > temp2Value) valueToCompare = temp2Value;
                if(valueToCompare > temp3Value) valueToCompare = temp3Value;
                Serial.println("using minumum value");
            break;
            case 1: //srednji
                if ((temp1Value <= temp2Value && temp2Value <= temp3Value) || (temp3Value <= temp2Value && temp2Value <= temp1Value)) {
                    valueToCompare = temp2Value;
                } else if ((temp2Value <= temp1Value && temp1Value <= temp3Value) || (temp3Value <= temp1Value && temp1Value <= temp2Value)) {
                    valueToCompare = temp1Value;
                } else {
                    valueToCompare = temp3Value;
                }
                Serial.println("using middle value");
                break;
            case 2: //maksimum
                valueToCompare = temp1Value;
                if(valueToCompare < temp2Value) valueToCompare = temp2Value;
                if(valueToCompare < temp3Value) valueToCompare = temp3Value;
                Serial.println("using maximum value");
            break;
            case 3: //srednja vrijednost
                valueToCompare = (temp1Value + temp2Value + temp3Value) / 3;
                Serial.println("using average value");

            break;
        }
        Serial.println(valueToCompare);

        if(wantedTemperature > valueToCompare){
            //need to turn ON heating
            changeHeatingRelayState(true);
        }
        else{
            //need to turn OFF heating
            changeHeatingRelayState(false);
        }
    }

    void changeHeatingRelayState(boolean state){
        Serial.println("enter change heating state function");
        if(heatingRelayState == state) return;

        if(millis() - heatingRelayStateTimer > 60 * 1000){
            Serial.println("timer OK");
            digitalWrite(heatingRelayPin, state);
            setButtonField(fieldGroup->getGroupId(), heatingStateField->getId(), state);
            heatingRelayState = state;
            heatingRelayStateTimer = millis();
        }
        else{
            Serial.println("timer NOT OK");
            
        }
    }

    void loop(){
        temperatureLoop1();
        temperatureLoop2();
        temperatureLoop3();
        temperatureLoop4();
        wantedTemperatureLoop();
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