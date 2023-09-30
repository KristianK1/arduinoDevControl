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

Adafruit_NeoPixel pixels(3, 13, NEO_GRB + NEO_KHZ800);
OneWire oneWire(4); 
DallasTemperature sensors(&oneWire);

void led1_changed(double value){
    int brightness = (int) (pow(1.12,value) - 1)*15.8;
    pixels.setPixelColor(0, pixels.Color(brightness,brightness,brightness));
    pixels.show();
}

void led2_changed(int value){
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
    pixels.setPixelColor(2, pixels.Color(r,g,b));
    pixels.show();
}

void led4_changed(bool value)
{
    digitalWrite(23, value);
}

void emptyFunction(double data){

}

class ThisDevice : protected FieldGroups, protected ComplexGroups
{
private:
    NumericField *field0 = 
        new NumericField(0, "LED 1", 0.0, 25.0, 1, "", "", led1_changed);

    MultipleChoiceField *field1 =
        new MultipleChoiceField(1, "LED 2", INPUT_FIELD, led2_changed, 5, "Off", "Red", "Green", "Blue", "White");

    RGBField *field2 =
        new RGBField(2, "LED 3", 0, 0, 0, led3_changed);
    
    FieldGroup *fieldGroup0 =
        new FieldGroup(0, "WS2812b", 3, field0, field1, field2);

    ButtonField *field3 =
        new ButtonField(1, "Blue LED", INPUT_FIELD, false, led4_changed);

    FieldGroup *fieldGroup1 =
        new FieldGroup(1, "LED", 1, field3);

    NumericField *potField = 
        new NumericField(0, "Potentiometer", 0.0, 4095.0, 1.0, "x =", "", emptyFunction);

    NumericField *tempField = 
        new NumericField(1, "Temperature", -50.0, 200.0, 0.25, "T=", "°C", emptyFunction);

    FieldGroup *fieldGroup2 =
        new FieldGroup(2, "Inputs", 2, potField, tempField);

    void potentiometerLoop(){
        int potValue = analogRead(34); //12bit
        Serial.println("potValue:");
        Serial.println(potValue);
        double currentValue = potField->getValue();

        Serial.println("oldValue:");
        Serial.println(currentValue);
        if(currentValue - potValue > 20 || currentValue - potValue < -20){
            // potField->setValue(String(potValue));
            setNumericField(fieldGroup2->getGroupId(), potField->getId(), potValue);
        }
    }

    void temperatureLoop(){
        sensors.begin();
        sensors.requestTemperatures(); // Send the command to get temperatures
        float tempC = sensors.getTempCByIndex(0);
        Serial.println(tempC);

        float currentValue = tempField->getValue();
        Serial.println(currentValue);

        float diff = currentValue - tempC;
        if(diff > 0.5 || diff < -0.5){
            // tempField->setValue(String(stringPayload) + " °C");
            setNumericField(fieldGroup2->getGroupId(), tempField->getId(), tempC);
        }
    }

public:
    void setupFields()
    {
        createGroups(2, fieldGroup0, fieldGroup1);
       
        pixels.begin();
        pinMode(23, OUTPUT);
        sensors.begin();
        
        createGroups(3, fieldGroup0, fieldGroup1, fieldGroup2);
        createComplexGroups(0);
    }

    void loop(){
        potentiometerLoop();
        temperatureLoop();
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
};

#endif