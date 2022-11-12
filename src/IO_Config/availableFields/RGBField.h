#ifndef RGB_FIELD_H
#define RGB_FIELD_H

#include "basicField.h"

#include "ArduinoJson.h"

typedef struct rgb
{
    int R, G, B; // [0,255] ?
} RGB;

class RGBField : public BasicField
{
private:
    RGB mValue;

public:
    RGBField(int fieldId, String fieldName, RGB value, void func())
    {
        mFieldId = fieldId;
        mFieldName = fieldName;
        mFieldDirection = INPUT_FIELD;
        mFieldType = "RGB";
        onChangeListener = func;

        mValue.R = value.R;
        mValue.G = value.G;
        mValue.B = value.B;

        DynamicJsonDocument doc(1024);
        doc["id"] = mFieldId;
        doc["fieldName"] = mFieldName;
        doc["fieldType"] = mFieldType;

        doc["fieldValue"]["R"] = mValue.R;
        doc["fieldValue"]["G"] = mValue.G;
        doc["fieldValue"]["B"] = mValue.B;

        doc["fieldValue"]["fieldDirection"] = "input";

        String myString;
        serializeJson(doc, myString);
        fieldInformation = myString;
    }

    RGBField(int fieldId, String fieldName, int R, int G, int B, void func())
    {
        mFieldId = fieldId;
        mFieldName = fieldName;

        onChangeListener = func;

        mValue.R = R;
        mValue.G = G;
        mValue.B = B;

        DynamicJsonDocument doc(1024);
        doc["id"] = mFieldId;
        doc["fieldName"] = mFieldName;
        doc["fieldType"] = "RGB";

        doc["fieldValue"]["R"] = mValue.R;
        doc["fieldValue"]["G"] = mValue.G;
        doc["fieldValue"]["B"] = mValue.B;

        doc["fieldValue"]["fieldDirection"] = "input";

        String myString;
        serializeJson(doc, myString);
        fieldInformation = myString;
    }

    virtual ~RGBField()
    {
    }

    RGB getValue()
    {
        return mValue;
    }

    void setValue(RGB value)
    {
        onChangeListener();
        mValue = value;
    }

    void setValue(int R, int G, int B)
    {
        mValue.B = R;
        mValue.G = G;
        mValue.B = B;
    }

    int getId()
    {
        return BasicField::getId();
    }
};

#endif