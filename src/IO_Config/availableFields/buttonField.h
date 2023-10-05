#ifndef BUTTON_FIELD_H
#define BUTTON_FIELD_H

#include "basicField.h"

#include "ArduinoJson.h"

class ButtonField : public BasicField
{
private:
    bool mValue;
    void (*onChangeListener)(bool);

public:
    ButtonField(int fieldId, String fieldName, int direction, bool value, void func(bool))
    {
        mFieldId = fieldId;
        mFieldName = fieldName;
        mFieldDirection = direction;
        mFieldType = "button";
        onChangeListener = func;

        mValue = value;

        DynamicJsonDocument doc(1024);
        doc["id"] = mFieldId;
        doc["fieldName"] = mFieldName;
        doc["fieldType"] = mFieldType;

        doc["fieldValue"]["fieldValue"] = mValue;
        if (direction == INPUT_FIELD)
        {
            doc["fieldValue"]["fieldDirection"] = "input";
        }
        else if (direction == OUTPUT_FIELD)
        {
            doc["fieldValue"]["fieldDirection"] = "output";
        }

        String myString;
        serializeJson(doc, myString);
        fieldInformation = myString;
    }

    virtual ~ButtonField()
    {
    }

    bool getValue()
    {
        return mValue;
    }

    void setValue(bool value)
    {
        onChangeListener(value);
        mValue = value;
    }

    void refresh(){
        onChangeListener(getValue());
    }

    int getId()
    {
        return BasicField::getId();
    }
};

#endif