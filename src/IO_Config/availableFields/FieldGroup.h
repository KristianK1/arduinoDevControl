#ifndef FIELD_GROUP_H
#define FIELD_GROUP_H

#include "BasicField.h"

class FieldGroup
{
private:
    int mGroupId;
    String mGroupName;
    BasicField **mFields;
    int mNofFields;

public:
    FieldGroup(int groupId, String groupName, int NofFields, ...)
    {
        mGroupId = groupId;
        mGroupName = groupName;
        mNofFields = NofFields;
        mFields = (BasicField **)calloc(mNofFields, sizeof(BasicField *));

        va_list arguments;
        va_start(arguments, NofFields);
        for (int x = 0; x < mNofFields; x++)
        {
            mFields[x] = va_arg(arguments, BasicField *);
        }
        va_end(arguments);
    }

    int getGroupId()
    {
        return mGroupId;
    }

    BasicField **getFields()
    {
        return mFields;
    }

    int getNofFields()
    {
        return mNofFields;
    }
};

class FieldGroups
{
private:
    FieldGroup **mFieldGroups;
    int NofGroups;

public:
    FieldGroup **getFieldGroups()
    {
        return mFieldGroups;
    }

    int getNumberOfGroups()
    {
        return NofGroups;
    }

    void createGroups(int n, ...)
    {
        NofGroups = n;
        mFieldGroups = (FieldGroup **)calloc(n, sizeof(FieldGroup *));
        va_list arguments;
        va_start(arguments, n);
        for (int i = 0; i < n; i++)
        {
            mFieldGroups[i] = va_arg(arguments, FieldGroup *);
        }
        va_end(arguments);
    }
};
#endif