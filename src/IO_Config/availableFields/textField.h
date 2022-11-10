#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#include "basicField.h"

class TextField : public BasicField
{
private:
    String mValue;

public:
    TextField(int fieldId, String fieldName, int direction, String value, void func(void))
    {
        mFieldId = fieldId;
        mFieldName = fieldName;
        mFieldDirection = direction;
        onChangeListener = func;

        mValue = value;

        DynamicJsonDocument doc(1024);
        doc["id"] = mFieldId;
        doc["fieldName"] = mFieldName;
        doc["fieldType"] = "text";

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

    virtual ~TextField()
    {
    }

    String getText()
    {
        return mValue;
    }

    void setValue(String value)
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