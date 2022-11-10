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
        Serial.println(info);
        return info;
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
                changeFieldValue_rgb(groupId, fieldId, R, G, B);
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
    void changeFieldInComplexGroup_button(int groupId, int stateId, int fieldId, boolean value)
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
        getTotalDeviceString();
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