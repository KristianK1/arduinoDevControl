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

#define Npixels 120
Adafruit_NeoPixel pixels(Npixels, 13, NEO_GRB + NEO_KHZ800);

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

void changeState(){
    Serial.println("Changed state");
}

void led_changed(bool value)
{
    digitalWrite(23, value);
}

void emptyFunction(double data){

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

    ComplexGroupState *inidividualRgbState = new ComplexGroupState(3, "Individualni RGB", 3, rgbField1, rgbField2, rgbField3);

    ComplexGroup *complexGroup = new ComplexGroup(0, "NOVA GRUPA", changeState, 4, brightnessState, colorSelectState, rgbState, inidividualRgbState);


    ButtonField *blueLed =
        new ButtonField(1, "Blue LED", INPUT_FIELD, false, led_changed);

    FieldGroup *fieldGroup1 =
        new FieldGroup(1, "LED", 1, blueLed);

    NumericField *potField = 
        new NumericField(0, "Potentiometer", OUTPUT_FIELD, 0.0, 4095.0, 1.0, "x =", "", emptyFunction);

    NumericField *tempField = 
        new NumericField(1, "Temperature",  OUTPUT_FIELD, -50.0, 200.0, 0.25, "T=", "°C", emptyFunction);

    FieldGroup *fieldGroup2 =
        new FieldGroup(2, "Inputs", 2, potField, tempField);
public:
    void setupFields()
    {
        createGroups(2, fieldGroup1, fieldGroup2);
       
        pixels.begin();
        pinMode(23, OUTPUT);
        sensors.begin();
        
        createComplexGroups(1, complexGroup);
    }

 void potentiometerLoop(){
        int potValue = analogRead(34); //12bit
        // Serial.println("potValue:");
        // Serial.println(potValue);
        double currentValue = potField->getValue();

        // Serial.println("oldValue:");
        // Serial.println(currentValue);
        if(currentValue - potValue > 50 || currentValue - potValue < -50){
            // potField->setValue(String(potValue));
            setNumericField(fieldGroup2->getGroupId(), potField->getId(), potValue);
        }
    }

    void temperatureLoop(){
        sensors.begin();
        sensors.requestTemperatures(); // Send the command to get temperatures
        float tempC = sensors.getTempCByIndex(0);
        // Serial.println(tempC);

        float currentValue = tempField->getValue();
        // Serial.println(currentValue);

        tempC = int(tempC / tempField->getStep()) * tempField->getStep();

        float diff = currentValue - tempC;
        if(diff >= 0.5 || diff <= -0.5){
            // tempField->setValue(String(stringPayload) + " °C");
            setNumericField(fieldGroup2->getGroupId(), tempField->getId(), tempC);
        }
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