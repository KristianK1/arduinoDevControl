#ifndef BUTTON_FIELD_H
#define BUTTON_FIELD_H

#include "basicField.h"

class ButtonField : public BasicField
{
private:
    boolean mValue;

public:
    ButtonField(int fieldId, String fieldName, boolean value, void func())
    {
        mFieldId = fieldId;
        mFieldName = fieldName;

        mValue = value;

        onChangeListener = func;
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