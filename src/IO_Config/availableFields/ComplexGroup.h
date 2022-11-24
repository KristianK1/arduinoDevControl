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
    String complexGroupStateInfo;

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

        for (int i = 0; i < nOfFields; i++)
        {
            for (int j = i + 1; j < nOfFields; j++)
            {
                if (mFields[i]->getId() > mFields[j]->getId())
                {
                    BasicField *swap = mFields[i];
                    mFields[i] = mFields[j];
                    mFields[j] = swap;
                }
            }
        }

        String info;
        info = "{\"id\":" + String(mStateId) + ", \"stateName\":\"" + mStateName + "\",\"fields\":[";
        for (int i = 0; i < nOfFields; i++)
        {
            info = info + mFields[i]->getFieldInfo();
            if (i != nOfFields - 1)
            {
                info = info + ",";
            }
        }
        info = info + "]}";
        complexGroupStateInfo = info;
    }

    int getStateId()
    {
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

    String getInfo()
    {
        return complexGroupStateInfo;
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
    int mCurrentState;
    String complexGroupInfo;

public:
    ComplexGroup(int groupId, String groupName, void func(), int n, ...)
    {
        mGroupId = groupId;
        mGroupName = groupName;
        mNofStates = n;
        onStateChangeListener = func;
        mCurrentState = 0;

        mStates = (ComplexGroupState **)calloc(mNofStates, sizeof(ComplexGroupState *));

        va_list arguments;
        va_start(arguments, n);
        for (int x = 0; x < n; x++)
        {
            mStates[x] = va_arg(arguments, ComplexGroupState *);
        }
        va_end(arguments);

        for (int i = 0; i < mNofStates; i++)
        {
            for (int j = i + 1; j < mNofStates; j++)
            {
                if (mStates[i]->getStateId() > mStates[j]->getStateId())
                {
                    ComplexGroupState *swap = mStates[i];
                    mStates[i] = mStates[j];
                    mStates[j] = swap;
                }
            }
        }

        String info = "{\"id\":" + String(mGroupId) + ",\"groupName\":\"" + mGroupName + "\",\"currentState\":" + mCurrentState + ",\"fieldGroupStates\":[";
        for (int i = 0; i < mNofStates; i++)
        {
            info = info + mStates[i]->getInfo();
            if (i != mNofStates - 1)
            {
                info = info + ",";
            }
        }
        info = info + "]}";
        complexGroupInfo = info;
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
            mCurrentState = n;
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

    String getInfo()
    {
        return complexGroupInfo;
    }
};

class ComplexGroups
{
private:
    ComplexGroup **mComplexGroups;
    int NofComplexGroups;
    String information;

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

        for (int i = 0; i < NofComplexGroups; i++)
        {
            for (int j = i + 1; j < NofComplexGroups; j++)
            {
                if (mComplexGroups[i]->getComplexGroupId() > mComplexGroups[j]->getComplexGroupId())
                {
                    ComplexGroup *swap = mComplexGroups[i];
                    mComplexGroups[i] = mComplexGroups[j];
                    mComplexGroups[j] = swap;
                }
            }
        }

        String info;
        info = "[";
        for (int i = 0; i < NofComplexGroups; i++)
        {
            info = info + mComplexGroups[i]->getInfo();
            if (i != NofComplexGroups - 1)
            {
                info = info + ",";
            }
        }
        info = info + "]";
        information = info;
    }

    String getInfo()
    {
        return information;
    }
};

#endif