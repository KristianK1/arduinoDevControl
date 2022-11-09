#ifndef NUMERIC_FIELD_H
#define NUMERIC_FIELD_H

#include "basicField.h"

class NumericField : public BasicField
{
private:
    double mMinValue;
    double mMaxValue;
    double mStep;
    double mValue;

public:
    NumericField(int fieldId, String fieldName, double minValue, double maxValue, double step, void func(void))
    {
        mFieldId = fieldId;
        mFieldName = fieldName;

        mMinValue = minValue;
        mMaxValue = maxValue;
        mStep = step;
        mValue = minValue;

        onChangeListener = func;
    }

    virtual ~NumericField() {}

    double getMin()
    {
        return mMinValue;
    }

    double getMax()
    {
        return mMaxValue;
    }

    double getStep()
    {
        return mStep;
    }

    double getValue()
    {
        return mValue;
    }

    void setValue(double value)
    {
        mValue = value;
        onChangeListener();
    }

    int getId()
    {
        Serial.println("neeeeeeeeeeee");
        return BasicField::getId();
    }
};

#endif