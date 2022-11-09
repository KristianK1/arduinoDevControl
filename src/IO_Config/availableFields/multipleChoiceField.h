#ifndef MULTIPLE_CHOICE_FIELD_H
#define MULTIPLE_CHOICE_FIELD_H

#include "basicField.h"

class MultipleChoiceField : public BasicField
{
private:
    String *mChoices;
    int NofChoices;
    int mValue;

public:
    MultipleChoiceField(int fieldId, String fieldName, void func(), int num, ...)
    {
        mFieldId = fieldId;
        mFieldName = fieldName;
        mChoices = (String *)calloc(num, sizeof(String));
        mValue = 0;
        NofChoices = num;

        onChangeListener = func;

        va_list arguments;        // A place to store the list of arguments
        va_start(arguments, num); // Initializing arguments to store all values after num

        for (int x = 0; x < num; x++)
            mChoices[x] = va_arg(arguments, char *); // Adds the next value in argument list to sum.
        va_end(arguments);
    }

    virtual ~MultipleChoiceField()
    {
    }

    String getValue()
    {
        return mChoices[mValue];
    }

    void setValue(int value)
    {
        if (value >= 0 && value < NofChoices)
        {
            onChangeListener();
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
                return;
            }
        }
    }

    int getId()
    {
        return BasicField::getId();
    }
};

#endif