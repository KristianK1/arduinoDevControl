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
        mFields = (BasicField **)calloc(NofFields, sizeof(BasicField *));

        va_list arguments;
        va_start(arguments, NofFields);
        for (int i = 0; i < NofFields; i++)
            mFields[i] = va_arg(arguments, BasicField *);
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
        mFieldGroups = (FieldGroup **)calloc(NofGroups, sizeof(FieldGroup *));
        va_list arguments;
        va_start(arguments, n);
        for (int i = 0; i < n; i++)
            mFieldGroups[i] = va_arg(arguments, FieldGroup *);
        va_end(arguments);
    }
};
#endif