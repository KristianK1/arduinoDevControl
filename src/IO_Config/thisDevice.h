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

    MultipleChoiceField *heatingType = 
        new MultipleChoiceField(20, "Heating type", INPUT_FIELD, emptyFunctionMCField, 3, "Minimum", "Average", "Maximum");

    NumericField *targetTemperature = 
        new NumericField(21, "Target temperature", INPUT_FIELD, 10.0, 30.0, 0.5, "", "°C", wantedTemperatureChanged);

    ButtonField *heatKristiansRoom = 
        new ButtonField(22, "Heat Kristian's room", INPUT_FIELD, false, emptyFunctionButtonField);

    ButtonField *heatLivingRoom = 
        new ButtonField(23, "Heat Living room", INPUT_FIELD, false, emptyFunctionButtonField);

    ButtonField *heatGoransRoom = 
        new ButtonField(24, "Heat Goran's room", INPUT_FIELD, false, emptyFunctionButtonField);

    ButtonField *heatingState = 
        new ButtonField(25, "Heater state", OUTPUT_FIELD, false, emptyFunctionButtonField);

    FieldGroup *heatingOptions =
        new FieldGroup(0, "Heating options", 6, heatingType, targetTemperature, heatKristiansRoom, heatLivingRoom, heatGoransRoom, heatingState);

    // ----------------------------------------------

    NumericField *KristiansRoomTemp = 
        new NumericField(0, "Kristian's room",  OUTPUT_FIELD, -20.0, 80.0, 0.5, "", "°C", emptyFunctionNumericField);

    NumericField *LivingRoomTemp = 
        new NumericField(1, "Living room", OUTPUT_FIELD, -20.0, 80.0, 0.5, "", "°C", emptyFunctionNumericField);

    NumericField *GoransRoomTemp = 
        new NumericField(2, "Goran's room",  OUTPUT_FIELD, -20.0, 80.0, 0.5, "", "°C", emptyFunctionNumericField);

    NumericField *HallwayTemp = 
        new NumericField(3, "Hallway", OUTPUT_FIELD, -20.0, 80.0, 0.5, "", "°C", emptyFunctionNumericField);

    FieldGroup *tempGroup =
        new FieldGroup(1, "Temperatures", 4, KristiansRoomTemp, LivingRoomTemp, GoransRoomTemp, HallwayTemp);



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
        

        createGroups(2, heatingOptions, tempGroup);        
        createComplexGroups(0);
    }


    void temperatureLoop(DallasTemperature sensor, NumericField *temperatureField, float stepPercentageLimit){
        sensor.begin();
        sensor.requestTemperatures(); // Send the command to get temperatures
        float tempC = sensor.getTempCByIndex(0);
        // Serial.println(tempC);

        float currentValue = temperatureField->getValue();
        // Serial.println(currentValue);

        double newTemp_normalized = int(tempC / temperatureField->getStep()) * temperatureField->getStep();

        float diff = currentValue - tempC;
        if(diff < 0){
            diff *= -1;
        }
        if(newTemp_normalized >= temperatureField->getMin() && newTemp_normalized <= temperatureField->getMax()){
            if(diff >= temperatureField->getStep() * stepPercentageLimit){
                setNumericField(tempGroup->getGroupId(), temperatureField->getId(), newTemp_normalized);
            }
        }
    }

    void wantedTemperatureLoop(){
        double Kvalue = KristiansRoomTemp->getValue();
        double Lvalue = LivingRoomTemp->getValue();
        double Gvalue = GoransRoomTemp->getValue();
        
        Serial.println("Temperature values: ");
        Serial.println(Kvalue);
        Serial.println(Lvalue);
        Serial.println(Gvalue);

        double valueToCompare = 0;
        int numberOfTemperatures = 0;

        switch (heatingType->getValue()){
            case 0: //minimum
                valueToCompare = 1000;
                if(heatKristiansRoom->getValue()){
                    if(Kvalue < valueToCompare){
                        valueToCompare = Kvalue;
                    }
                }
                if(heatLivingRoom->getValue()){
                    if(Lvalue < valueToCompare){
                        valueToCompare = Lvalue;
                    }
                }
                if(heatGoransRoom->getValue()){
                    if(Gvalue < valueToCompare){
                        valueToCompare = Gvalue;
                    }
                }
                Serial.println("using minumum value");
                break;
            case 1: //average
                if(heatKristiansRoom->getValue()){
                    valueToCompare += Kvalue;
                    Serial.println("dodaj K");
                    numberOfTemperatures++;
                }
                if(heatLivingRoom->getValue()){
                    valueToCompare += Lvalue;
                    Serial.println("dodaj L");
                    numberOfTemperatures++;
                }
                if(heatGoransRoom->getValue()){
                    valueToCompare += Gvalue;
                    Serial.println("dodaj G");
                    numberOfTemperatures++;
                }

                if(numberOfTemperatures > 0){
                    valueToCompare/=numberOfTemperatures;
                }
                else{
                    valueToCompare = 1000;
                }
                Serial.println("using middle value");
                break;
            case 2: //maksimum
                valueToCompare = -1000;
                bool validValues = false;
                if(heatKristiansRoom->getValue()){
                    if(Kvalue > valueToCompare){
                        valueToCompare = Kvalue;
                        validValues = true;
                    }
                }
                if(heatLivingRoom->getValue()){
                    if(Lvalue > valueToCompare){
                        valueToCompare = Lvalue;
                        validValues = true;
                    }
                }
                if(heatGoransRoom->getValue()){
                    if(Gvalue > valueToCompare){
                        valueToCompare = Gvalue;
                        validValues = true;
                    }
                }

                if(validValues == false){
                    valueToCompare = 1000;
                }
                Serial.println("using maximum value");
                break;
        }
        Serial.println(valueToCompare);

        double wantedTemperature = targetTemperature->getValue();

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
            setButtonField(heatingOptions->getGroupId(), heatingState->getId(), state);
            Serial.println("setting state");
            Serial.println(heatingRelayState);
            Serial.println(state);
            heatingRelayState = state;
            heatingRelayStateTimer = millis();
        }
        else{
            Serial.println("timer NOT OK");
            
        }
    }

    void loop(){
        temperatureLoop(sensors1, KristiansRoomTemp, 1);
        temperatureLoop(sensors2, LivingRoomTemp,1);
        temperatureLoop(sensors3, GoransRoomTemp,1);
        temperatureLoop(sensors4, HallwayTemp, 1);
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