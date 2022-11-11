#ifndef NUMERIC_FIELD_H
#define NUMERIC_FIELD_H

#include "basicField.h"

#include "ArduinoJson.h"

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
        mFieldDirection = INPUT_FIELD;
        mFieldType = "numeric";
        onChangeListener = func;

        mMinValue = minValue;
        mMaxValue = maxValue;
        mStep = step;
        mValue = minValue;

        DynamicJsonDocument doc(1024);
        doc["id"] = mFieldId;
        doc["fieldName"] = mFieldName;
        doc["fieldType"] = mFieldType;

        doc["fieldValue"]["fieldValue"] = mValue;
        doc["fieldValue"]["minValue"] = mMinValue;
        doc["fieldValue"]["maxValue"] = mMaxValue;
        doc["fieldValue"]["valueStep"] = mStep;

        doc["fieldValue"]["fieldDirection"] = "input";

        String myString;
        serializeJson(doc, myString);
        fieldInformation = myString;
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
        return BasicField::getId();
    }
};

#endif