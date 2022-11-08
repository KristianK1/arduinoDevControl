#ifndef IO_H
#define IO_H

#include "ArduinoJson.h"
#include "thisDevice.h"

class IO : ThisDevice
{
private:

public:
    void print(){

    }

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
                const char* text = doc["data"]["value"]["text"];
                changeFieldValue_text(groupId, fieldId, text);
            }
            else if (strcmp(fieldType, "button") == 0)
            {
                boolean onOff = doc["data"]["value"]["onOff"];
                changeFieldValue_button(groupId, fieldId, onOff);
            }
            else if (strcmp(fieldType, "multipleChoice") == 0)
            {
                const char* value = doc["data"]["value"]["choice"];
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
            const char* state = doc["data"]["state"];
        }
    }

    void changeFieldValue_numeric(int groupId, int fieldId, double value)
    {
    }

    void changeFieldValue_text(int groupId, int fieldId, String value)
    {
    }

    void changeFieldValue_button(int groupId, int fieldId, boolean value)
    {
    }

    void changeFieldValue_multiple(int groupId, int fieldId, String value)
    {
    }

    void changeFieldValue_RGB(int groupId, int fieldId, int R, int G, int B)
    {
    }
};

#endif