#ifndef IO_H
#define IO_H

#include "ArduinoJson.h"
#include "thisDevice.h"
#include <typeinfo>

class IO : public ThisDevice
{
private:
public:
    void loop()
    {
    }

    void reciveData(String data)
    {
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, data.c_str());

        const char *whatToAlter = doc["whatToAlter"];
        if (strcmp(whatToAlter, "field") == 0)
        {
            int groupId = doc["data"]["groupId"];
            int fieldId = doc["data"]["fieldId"];

            const char *fieldType = doc["data"]["fieldType"];
            if (strcmp(fieldType, "numeric") == 0)
            {
                double value = doc["data"]["value"]["number"];
                changeFieldValue_numeric(groupId, fieldId, value);
            }
            else if (strcmp(fieldType, "text") == 0)
            {
                const char *text = doc["data"]["value"]["text"];
                changeFieldValue_text(groupId, fieldId, text);
            }
            else if (strcmp(fieldType, "button") == 0)
            {
                boolean onOff = doc["data"]["value"]["onOff"];
                changeFieldValue_button(groupId, fieldId, onOff);
            }
            else if (strcmp(fieldType, "multipleChoice") == 0)
            {
                int value = doc["data"]["value"]["choice"];
                changeFieldValue_multiple(groupId, fieldId, value);
            }
            else if (strcmp(fieldType, "RGB") == 0)
            {
                int R = doc["data"]["value"]["R"];
                int G = doc["data"]["value"]["G"];
                int B = doc["data"]["value"]["B"];
                changeFieldValue_RGB(groupId, fieldId, R, G, B);
            }
        }
        else if (strcmp(whatToAlter, "complexGroupState") == 0)
        {
            int groupId = doc["data"]["groupId"];
            const char *state = doc["data"]["state"];
        }
        else if (strcmp(whatToAlter, "fieldInComplexGroup") == 0)
        {
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

    void changeFieldValue_button(int groupId, int fieldId, boolean value)
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

    void changeFieldValue_RGB(int groupId, int fieldId, int R, int G, int B)
    {
        BasicField *field = findFieldById(groupId, fieldId);
        RGBField *fieldAdd = (RGBField *)field;
        fieldAdd->setValue(R, G, B);
    }

    //////////////////////////////////////////////////////////////////////////////////

    FieldGroup *findGroupById(int groupId)
    {
        Serial.println("hello9");
        for (int i = 0; i < getNumberOfGroups(); i++)
        {
            Serial.println("hello10");
            if (getFieldGroups()[i]->getGroupId() == groupId)
            {
                Serial.println("hello11");
                return getFieldGroups()[i];
            }
        }
    }

    BasicField *findFieldById(int groupId, int fieldId)
    {
        Serial.println("hello8");

        FieldGroup *group = findGroupById(groupId);
        for (int i = 0; i < group->getNofFields(); i++)
        {
            Serial.println("hello8.1");
            Serial.println(group->getFields()[i]->getId());
            if (group->getFields()[i]->getId() == fieldId)
            {
                Serial.println("hello8.2");
                return group->getFields()[i];
            }
        }
    }

    ComplexGroup *findComplexGroupById(int groupId)
    {
        for (int i = 0; i < getNumberOfComplexGroups(); i++)
        {
            if (getComplexGroups()[i]->getComplexGroupId() == groupId)
            {
                return getComplexGroups()[i];
            }
        }
    }

    ComplexGroupState *findComplexGroupState(int groupId, int stateId)
    {
        ComplexGroup *group = findComplexGroupById(groupId);
        for (int i = 0; i < group->getNofStates(); i++)
        {
            if (group->getStates()[i]->getStateId() == stateId)
            {
                return group->getStates()[i];
            }
        }
    }

    BasicField *findFieldinComplexGroup(int groupId, int stateId, int fieldId)
    {
        ComplexGroupState *state = findComplexGroupState(groupId, stateId);
        for (int i = 0; i < state->getNumberOfFields(); i++)
        {
            if (state->getFields()[i]->getId() == fieldId)
            {
                return state->getFields()[i];
            }
        }
    }

    ///////////////////////////////////////////////////////

    void test()
    {
        setupFields();
        {
            Serial.println("hello7");
            BasicField *field = findFieldById(0, 0);
            Serial.println("hello99");
            NumericField *fieldAdd = (NumericField *)field;
            Serial.println(String(fieldAdd->getMin()));
            Serial.println(String(fieldAdd->getMax()));
            Serial.println(String(fieldAdd->getStep()));
            fieldAdd->setValue(23);
            Serial.println(String(fieldAdd->getValue()));
        }
        {
            BasicField *field = findFieldinComplexGroup(1, 1, 0);
            RGBField *fieldRGB = (RGBField *)field;
            RGB stateToSet;
            stateToSet.R = 25;
            stateToSet.G = 35;
            stateToSet.B = 45;
            fieldRGB->setValue(stateToSet);
            RGB state = fieldRGB->getValue();
            Serial.println(state.R);
            Serial.println(state.G);
            Serial.println(state.B);
        }
    }
};

#endif