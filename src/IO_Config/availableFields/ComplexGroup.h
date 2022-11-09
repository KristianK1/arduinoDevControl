#ifndef COMPLEX_GROUP_H
#define COMPLEX_GROUP_H

#include "basicField.h"

class ComplexGroupState
{
private:
    int mStateId;
    String mStateName;
    BasicField **mFields;
    int nOfFields;

public:
    ComplexGroupState(int stateId, String stateName, int n, ...)
    {
        mStateId = stateId;
        mStateName = stateName;
        nOfFields = n;
        mFields = (BasicField **)calloc(nOfFields, sizeof(BasicField *));

        va_list arguments;
        va_start(arguments, n);
        for (int x = 0; x < n; x++)
        {
            mFields[x] = va_arg(arguments, BasicField *);
        }
        va_end(arguments);
    }

    int getStateId(){
        return mStateId;
    }
    
    BasicField **getFields()
    {
        return mFields;
    }

    int getNumberOfFields()
    {
        return nOfFields;
    }
};

class ComplexGroup
{
private:
    int mGroupId;
    String mGroupName;
    ComplexGroupState **mStates;
    int mNofStates;
    void (*onStateChangeListener)(void);
    int currentState;

public:
    ComplexGroup(int groupId, String groupName, void func(), int n, ...)
    {
        mGroupId = groupId;
        mGroupName = groupName;
        mNofStates = n;
        onStateChangeListener = func;

        mStates = (ComplexGroupState **)calloc(mNofStates, sizeof(ComplexGroupState *));

        va_list arguments;
        va_start(arguments, n);
        for (int x = 0; x < n; x++)
        {
            mStates[x] = va_arg(arguments, ComplexGroupState *);
        }
        va_end(arguments);
    }

    int getComplexGroupId()
    {
        return mGroupId;
    }

    void changeState(int n)
    {
        if (n >= 0 && n <= mNofStates)
        {
            onStateChangeListener();
            currentState = n;
        }
    }

    ComplexGroupState **getStates()
    {
        return mStates;
    }

        int getNofStates()
    {
        return mNofStates;
    }
};

class ComplexGroups
{
private:
    ComplexGroup **mComplexGroups;
    int NofComplexGroups;

public:
    ComplexGroup **getComplexGroups()
    {
        return mComplexGroups;
    }

    int getNumberOfComplexGroups()
    {
        return NofComplexGroups;
    }

    void createComplexGroups(int n, ...)
    {
        NofComplexGroups = n;
        mComplexGroups = (ComplexGroup **)calloc(n, sizeof(ComplexGroup *));
        va_list arguments;
        va_start(arguments, n);
        for (int i = 0; i < n; i++)
        {
            mComplexGroups[i] = va_arg(arguments, ComplexGroup *);
        }
        va_end(arguments);
    }
};

#endif