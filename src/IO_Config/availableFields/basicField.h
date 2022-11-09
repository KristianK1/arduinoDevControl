#ifndef BASIC_FIELD_H
#define BASIC_FIELD_H

class BasicField
{
protected:
    int mFieldId;
    String mFieldName;

public:
    int getId()
    {
        return mFieldId;
    }
};

#endif