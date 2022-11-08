#ifndef MULTIPLE_CHOICE_FIELD_H
#define MULTIPLE_CHOICE_FIELD_H

class MultipleChoiceField
{
private:
    int mFieldId;
    String mFieldName;

    String *mChoices;
    int NofChoices;
    int mValue;

public:
    MultipleChoiceField(int fieldId, String fieldName, int num, ...)
    {

        mFieldId = fieldId;
        mFieldName = fieldName;
        mChoices = (String *)calloc(num, sizeof(String));
        mValue = 0;
        
        va_list arguments;        // A place to store the list of arguments
        va_start(arguments, num); // Initializing arguments to store all values after num

        for (int x = 0; x < num; x++)
            mChoices[x] = va_arg(arguments, char *); // Adds the next value in argument list to sum.
        va_end(arguments);
    }

    virtual ~MultipleChoiceField()
    {
    }

    boolean getValue()
    {
        return mChoices[mValue];
    }

    void setValue(int value)
    {
        if (value < NofChoices)
        {
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

    int getFieldId()
    {
        return mFieldId;
    }
};

#endif