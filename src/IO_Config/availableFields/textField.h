#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

class TextField
{
private:
    int mFieldId;
    String mFieldName;

    String mValue;

public:
    TextField(int fieldId, String fieldName, String value)
    {
        mFieldId = fieldId;
        mFieldName = fieldName;
        
        mValue = value;
    }

    virtual ~TextField()
    {
    }

    String getValue()
    {
        return mValue;
    }

    void setValue(String value)
    {
        mValue = value;
    }

    int getFieldId()
    {
        return mFieldId;
    }
};

#endif