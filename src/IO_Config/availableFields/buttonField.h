#ifndef BUTTON_FIELD_H
#define BUTTON_FIELD_H

#include "basicField.h"

class ButtonField : public BasicField
{
private:
    boolean mValue;

public:
    ButtonField(int fieldId, String fieldName, int direction, boolean value, void func())
    {
        mFieldId = fieldId;
        mFieldName = fieldName;
        mFieldDirection = direction;
        onChangeListener = func;

        mValue = value;

        DynamicJsonDocument doc(1024);
        doc["id"] = mFieldId;
        doc["fieldName"] = mFieldName;
        doc["fieldType"] = "button";

        doc["fieldValue"] = mValue;
        if (direction == INPUT_FIELD)
        {
            doc["fieldDirection"] = "input";
        }
        else if (direction == OUTPUT_FIELD)
        {
            doc["fieldDirection"] = "output";
        }
        
        String myString;
        serializeJson(doc, myString);
        fieldInformation = myString;
    }

    virtual ~ButtonField()
    {
    }

    boolean getValue()
    {
        return mValue;
    }

    void setValue(boolean value)
    {
        onChangeListener();
        mValue = value;
    }

    int getId()
    {
        return BasicField::getId();
    }
};

#endif