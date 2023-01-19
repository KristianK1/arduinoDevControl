#ifndef IO_H
#define IO_H

#include "ArduinoJson.h"
#include "thisDevice.h"
#include <typeinfo>

#include "../deviceKey.h"

class IO : public ThisDevice
{
private:
    String information;

public:
    void loop()
    {
    }

    String getTotalDeviceString()
    {
        String info = "{\"deviceKey\":\"" + deviceKey + "\"";

        if (getNumberOfGroups() > 0)
        {
            info = info + ",";
            info = info + "\"deviceFieldGroups\":" + FieldGroups::getInfo();
        }
        if (getNumberOfComplexGroups() > 0)
        {
            info = info + ",";
            info = info + "\"deviceFieldComplexGroups\":" + ComplexGroups::getInfo();
        }
        info = info + "}";
        // Serial.println(info);
        return info;
    }

 void wsDataParser(String data){
        String groupsKey = "deviceFieldGroups";
        String complexGroupsKey = "deviceFieldComplexGroups";
        DynamicJsonDocument doc(10000);
        deserializeJson(doc, data);
        
        int NofGroups = FieldGroups::getNumberOfGroups();
        for(int i = 0; i<NofGroups; i++){
            FieldGroup group = *(FieldGroups::getFieldGroups()[i]);

            for(int j = 0; j < group.getNofFields(); j++){
                BasicField *field = group.getFields()[j];
                
                String fieldType = field->getFieldType().c_str();
                Serial.println("|" + fieldType);
                if(strcmp(fieldType.c_str(),"numeric") == 0){
                    Serial.println("proso numeric");
                    void *pointer = field;
                    NumericField *numericField = (NumericField*)pointer;
                    double value = doc["deviceFieldGroups"][i]["fields"][j]["fieldValue"]["fieldValue"];
                    Serial.print("numeric value: ");
                    Serial.println(value);
                    if(numericField->getValue() != value){
                        Serial.println("numeric1_parser");
                        Serial.println(numericField->getValue());
                        Serial.println(numericField->getFieldType());
                        Serial.println(numericField->getFieldInfo());
                        changeFieldValue_numeric(group.getGroupId(), field->getId(), value);
                    }
                }
                else if(strcmp(fieldType.c_str(),"text") == 0){
                    Serial.println("proso text");
                    void *pointer = field;
                    TextField *textField = (TextField*)pointer;
                    String value = doc["deviceFieldGroups"][i]["fields"][j]["fieldValue"]["fieldValue"];
                    if(textField->getText().compareTo(value)){
                        changeFieldValue_text(group.getGroupId(), field->getId(), value);
                    }
                }
                else if(strcmp(fieldType.c_str(),"button") == 0){
                    Serial.println("proso button");
                    void *pointer = field;
                    ButtonField *buttonField = (ButtonField*)pointer;

                    bool value = doc["deviceFieldGroups"][i]["fields"][j]["fieldValue"]["fieldValue"];
                    Serial.print("button value: ");
                    Serial.println(value);
                    if(buttonField->getValue() != value){
                        Serial.println("button1_parser");
                        if(buttonField->getValue() == false){
                            Serial.println("0false");
                        }
                        else if(buttonField->getValue() == true){
                            Serial.println("1true");
                        }
                        else{
                            Serial.println("pakao zivi");
                        }
                        changeFieldValue_button(group.getGroupId(), field->getId(), value);
                    }
                }
                else if(strcmp(fieldType.c_str(),"multipleChoice") == 0){
                    Serial.println("proso mc");
                    void *pointer = field;
                    MultipleChoiceField *multipleChoiceField = (MultipleChoiceField*)pointer;
                    int value = doc["deviceFieldGroups"][i]["fields"][j]["fieldValue"]["fieldValue"];
                    if(multipleChoiceField->getValue() != value){
                        changeFieldValue_multiple(group.getGroupId(), field->getId(), value);
                    }
                }
                else if(strcmp(fieldType.c_str(),"RGB") == 0){
                    Serial.println("proso rgb");
                    void *pointer = field;
                    RGBField *rgbField = (RGBField*)pointer;
                    int valueR = doc["deviceFieldGroups"][i]["fields"][j]["fieldValue"]["R"];
                    int valueG = doc["deviceFieldGroups"][i]["fields"][j]["fieldValue"]["G"];
                    int valueB = doc["deviceFieldGroups"][i]["fields"][j]["fieldValue"]["B"];
                    RGB currentValue = rgbField->getValue();
                    if(currentValue.R != valueR || currentValue.G != valueG || currentValue.B != valueB){
                        changeFieldValue_rgb(group.getGroupId(), field->getId(), valueR, valueG, valueB);
                    }
                }
                else{
                    Serial.println("KRIVI TIP FIELDA");
                    Serial.println(fieldType.c_str());
                }
            }
        }
    }

    void changeFieldValue_numeric(int groupId, int fieldId, double value)
    {
        BasicField *field = findFieldById(groupId, fieldId);
        NumericField *fieldAdd = (NumericField *)field;
        fieldAdd->setValue(value);
    }

    void changeFieldValue_text(int groupId, int fieldId, String value)
    {
        BasicField *field = findFieldById(groupId, fieldId);
        TextField *fieldAdd = (TextField *)field;
        fieldAdd->setValue(value);
    }

    void changeFieldValue_button(int groupId, int fieldId, bool value)
    {
        BasicField *field = findFieldById(groupId, fieldId);
        ButtonField *fieldAdd = (ButtonField *)field;
        fieldAdd->setValue(value);
    }

    void changeFieldValue_multiple(int groupId, int fieldId, int value)
    {
        BasicField *field = findFieldById(groupId, fieldId);
        MultipleChoiceField *fieldAdd = (MultipleChoiceField *)field;
        fieldAdd->setValue(value);
    }

    void changeFieldValue_rgb(int groupId, int fieldId, int R, int G, int B)
    {
        BasicField *field = findFieldById(groupId, fieldId);
        RGBField *fieldAdd = (RGBField *)field;
        fieldAdd->setValue(R, G, B);
    }

    void changeComplexGroupState(int groupId, int stateId)
    {
        ComplexGroup *complexGroup = findComplexGroupById(groupId);
        complexGroup->changeState(stateId);
    }
    ////////////////////
    void changeFieldInComplexGroup_numeric(int groupId, int stateId, int fieldId, double value)
    {
        BasicField *field = findFieldinComplexGroup(groupId, stateId, fieldId);
        NumericField *fieldAdd = (NumericField *)field;
        fieldAdd->setValue(value);
    }

    void changeFieldInComplexGroup_text(int groupId, int stateId, int fieldId, String value)
    {
        BasicField *field = findFieldinComplexGroup(groupId, stateId, fieldId);
        TextField *fieldAdd = (TextField *)field;
        fieldAdd->setValue(value);
    }
    void changeFieldInComplexGroup_button(int groupId, int stateId, int fieldId, bool value)
    {
        BasicField *field = findFieldinComplexGroup(groupId, stateId, fieldId);
        ButtonField *fieldAdd = (ButtonField *)field;
        fieldAdd->setValue(value);
    }
    void changeFieldInComplexGroup_multiple(int groupId, int stateId, int fieldId, int value)
    {
        BasicField *field = findFieldinComplexGroup(groupId, stateId, fieldId);
        MultipleChoiceField *fieldAdd = (MultipleChoiceField *)field;
        fieldAdd->setValue(value);
    }
    void changeFieldInComplexGroup_rgb(int groupId, int stateId, int fieldId, int R, int G, int B)
    {
        BasicField *field = findFieldinComplexGroup(groupId, stateId, fieldId);
        RGBField *fieldAdd = (RGBField *)field;
        fieldAdd->setValue(R, G, B);
    }

    //////////////////////////////////////////////////////////////////////////////////

    FieldGroup *findGroupById(int groupId)
    {
        for (int i = 0; i < getNumberOfGroups(); i++)
        {
            if (getFieldGroups()[i]->getGroupId() == groupId)
            {
                return getFieldGroups()[i];
            }
        }
        return NULL;
    }

    BasicField *findFieldById(int groupId, int fieldId)
    {
        FieldGroup *group = findGroupById(groupId);
        if (group == NULL)
        {
            return NULL;
        }

        for (int i = 0; i < group->getNofFields(); i++)
        {
            if (group->getFields()[i]->getId() == fieldId)
            {
                return group->getFields()[i];
            }
        }
        return NULL;
    }

    /////////////////

    ComplexGroup *findComplexGroupById(int groupId)
    {
        for (int i = 0; i < getNumberOfComplexGroups(); i++)
        {
            if (getComplexGroups()[i]->getComplexGroupId() == groupId)
            {
                return getComplexGroups()[i];
            }
        }
        return NULL;
    }

    ComplexGroupState *findComplexGroupState(int groupId, int stateId)
    {
        ComplexGroup *group = findComplexGroupById(groupId);
        if (group == NULL)
        {
            return NULL;
        }

        for (int i = 0; i < group->getNofStates(); i++)
        {
            if (group->getStates()[i]->getStateId() == stateId)
            {
                return group->getStates()[i];
            }
        }
        return NULL;
    }

    BasicField *findFieldinComplexGroup(int groupId, int stateId, int fieldId)
    {
        ComplexGroupState *state = findComplexGroupState(groupId, stateId);
        if (state == NULL)
        {
            return NULL;
        }

        for (int i = 0; i < state->getNumberOfFields(); i++)
        {
            if (state->getFields()[i]->getId() == fieldId)
            {
                return state->getFields()[i];
            }
        }
        return NULL;
    }

    ///////////////////////////////////////////////////////

    void test()
    {
        setupFields();
        // getTotalDeviceString();
        // {
        //     BasicField *field = findFieldById(0, 0);
        //     NumericField *fieldAdd = (NumericField *)field;
        //     fieldAdd->setValue(23);
        // }
        // {
        //     BasicField *field = findFieldinComplexGroup(1, 1, 0);
        //     RGBField *fieldRGB = (RGBField *)field;
        // }
    }
};

#endif