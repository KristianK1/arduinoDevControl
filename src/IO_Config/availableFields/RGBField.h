#ifndef RGB_FIELD_H
#define RGB_FIELD_H

#include "basicField.h"

typedef struct rgb
{
    int R, G, B; // [0,255] ?
} RGB;

class RGBField : public BasicField
{
private:
    RGB mValue;

public:
    RGBField(int fieldId, String fieldName, RGB value)
    {
        mFieldId = fieldId;
        mFieldName = fieldName;

        mValue.B = value.R;
        mValue.G = value.G;
        mValue.B = value.B;
    }

    RGBField(int fieldId, String fieldName, int R, int G, int B)
    {
        mFieldId = fieldId;
        mFieldName = fieldName;

        mValue.B = R;
        mValue.G = G;
        mValue.B = B;
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