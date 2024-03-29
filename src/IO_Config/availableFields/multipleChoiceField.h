#ifndef MULTIPLE_CHOICE_FIELD_H
#define MULTIPLE_CHOICE_FIELD_H

#include "basicField.h"

#include "ArduinoJson.h"

class MultipleChoiceField : public BasicField
{
private:
    String *mChoices;
    int NofChoices;
    int mValue;
    void (*onChangeListener)(int);

public:
    MultipleChoiceField(int fieldId, String fieldName, int direction, void func(int), int num, ...)
    {
        mFieldId = fieldId;
        mFieldName = fieldName;
        mFieldDirection = direction;
        mFieldType = "multipleChoice";
        onChangeListener = func;

        mChoices = (String *)calloc(num, sizeof(String));
        NofChoices = num;
        mValue = 0;

        va_list arguments;        // A place to store the list of arguments
        va_start(arguments, num); // Initializing arguments to store all values after num

        for (int x = 0; x < num; x++)
            mChoices[x] = va_arg(arguments, char *); // Adds the next value in argument list to sum.
        va_end(arguments);

        DynamicJsonDocument doc(1024);
        doc["id"] = mFieldId;
        doc["fieldName"] = mFieldName;
        doc["fieldType"] = mFieldType;

        for (int i = 0; i < NofChoices; i++)
        {
            doc["fieldValue"]["values"][i] = mChoices[i];
        }

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

    virtual ~MultipleChoiceField()
    {
    }

    int getValue()
    {
        return mValue;
    }

    void setValue(int value)
    {
        if (value >= 0 && value < NofChoices)
        {
            onChangeListener(value);
            mValue = value;
        }
    }

    void setValue(char *value)
    {
        for (int i = 0; i < NofChoices; i++)
        {
            if (strcmp(mChoices[i].c_str(), value) == 0)
            {
                mValue = i;
                onChangeListener(mValue);
                return;
            }
        }
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