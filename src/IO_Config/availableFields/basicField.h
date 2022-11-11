#ifndef BASIC_FIELD_H
#define BASIC_FIELD_H

#define INPUT_FIELD 0
#define OUTPUT_FIELD 1

class BasicField
{
protected:
    int mFieldId;
    String mFieldName;
    void (*onChangeListener)(void);
    
    int mFieldDirection; //INPUT OR OUTPUT
    String fieldInformation;
    String mFieldType;

public:
    int getId()
    {
        return mFieldId;
    }

    String getFieldInfo(){
        return fieldInformation;
    }

    String getFieldType(){
        return mFieldType;
    }
};

#endif