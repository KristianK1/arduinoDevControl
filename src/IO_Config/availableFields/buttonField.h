#ifndef BUTTON_FIELD_H
#define BUTTON_FIELD_H

class ButtonField
{
private:
    int mFieldId;
    String mFieldName;

    boolean mValue;

public:
    ButtonField(int fieldId, String fieldName, boolean value)
    {
        mFieldId = fieldId;
        mFieldName = fieldName;
        
        mValue = value;
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
        mValue = value;
    }

    int getFieldId()
    {
        return mFieldId;
    }
};

#endif