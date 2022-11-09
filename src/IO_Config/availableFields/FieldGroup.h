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
    FieldGroup(int groupId, String groupName, BasicField **fields, int NofFields)
    {
        mGroupId = groupId;
        mGroupName = groupName;
        mFields = fields;
        mNofFields = NofFields;
    }

    int getGroupId()
    {
        return mGroupId;
    }

    BasicField** getFields()
    {
        return mFields;
    }

    int getNofFields(){
        return mNofFields;
    }
};

#endif