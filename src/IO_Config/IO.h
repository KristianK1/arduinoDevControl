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

    FieldGroup *findGroupById(int groupId)
    {
        for (int i = 0; i < getNumberOfGroups(); i++)
        {
            if (getFieldGroups()[i]->getGroupId() == groupId)
            {
                return getFieldGroups()[i];
            }
        }
    }

    BasicField *findFieldById(int groupId, int fieldId)
    {
        FieldGroup *group = findGroupById(groupId);
        for (int i = 0; i < group->getNofFields(); i++)
        {
            if (group->getFields()[i]->getId() == fieldId)
            {
                return group->getFields()[i];
            }
        }
    }

    void test()
    {
        setupFields();
        {
            BasicField *field = findFieldById(98, 0);
            NumericField *fieldAdd = (NumericField *)field;
            Serial.println(String(fieldAdd->getMin()));
            Serial.println(String(fieldAdd->getMax()));
            Serial.println(String(fieldAdd->getStep()));
            fieldAdd->setValue(23);
            Serial.println(String(fieldAdd->getValue()));
        }
        // {
        //     BasicField *field = findFieldById(0, 1);
        //     NumericField *fieldAdd = (NumericField *)field;
        //     Serial.println(String(fieldAdd->getMin()));
        //     Serial.println(String(fieldAdd->getMax()));
        //     Serial.println(String(fieldAdd->getStep()));
        // }
    }
};

#endif