#ifndef THIS_DEVICE_H
#define THIS_DEVICE_H

#include "availableFields/numericField.h"
#include "availableFields/textField.h"
#include "availableFields/buttonField.h"
#include "availableFields/RGBField.h"
#include "availableFields/multipleChoiceField.h"
#include "availableFields/basicField.h"
#include "availableFields/FieldGroup.h"
#include "availableFields/ComplexGroup.h"

#include "ArduinoJson.h"

void emptyFunctionNumeric(double value){

}

void emptyFunctionButton(bool value){

}

void emptyFunctionText(String value){

}

void emptyFunctionMC(int value){

}

void emptyFunctionRGB(int r, int g, int b){

}
class ThisDevice : protected FieldGroups, protected ComplexGroups
{
private:

    NumericField *field1 = 
        new NumericField(0, "f1", INPUT_FIELD, 0.5, 5.5, 1.0, "", "",  emptyFunctionNumeric);

    NumericField *field2 = 
        new NumericField(1, "f2", INPUT_FIELD, 0.5, 5.5, 2.5, "", "",  emptyFunctionNumeric);

    ButtonField *field3 = 
        new ButtonField(2, "f3", INPUT_FIELD, false, emptyFunctionButton);

    ButtonField *field4 = 
        new ButtonField(3, "f4", INPUT_FIELD, false, emptyFunctionButton);

    TextField *field5 = 
        new TextField(4, "f5", INPUT_FIELD, "", emptyFunctionText);
    
    TextField *field6 = 
        new TextField(5, "f6", INPUT_FIELD, "", emptyFunctionText);

    MultipleChoiceField *field7 = 
        new MultipleChoiceField(6, "f7", INPUT_FIELD, emptyFunctionMC, 3, "One", "Two", "Three");

    MultipleChoiceField *field8 = 
        new MultipleChoiceField(7, "f8", INPUT_FIELD, emptyFunctionMC, 3, "One", "Two", "Three");

    RGBField *field9 = 
        new RGBField(8, "f9", 0, 0, 0, emptyFunctionRGB);

    RGBField *field10 = 
        new RGBField(9, "f10", 0, 0, 0, emptyFunctionRGB);

    FieldGroup *group = 
        new FieldGroup(0, "group", 10, field1, field2, field3, field4, field5, field6, field7, field8, field9, field10);

public:
    void setupFields()
    {
        createGroups(1, group);       
        createComplexGroups(0);
    }

    void loop(){
    }

    virtual double getNumericFieldValue(int groupId, int fieldId) = 0;
    virtual String getTextFieldValue(int groupId, int fieldId) = 0;
    virtual bool getButtonFieldValue(int groupId, int fieldId) = 0;
    virtual int getMCFieldValue(int groupId, int fieldId) = 0;
    virtual RGB getRGBFieldValue(int groupId, int fieldId) = 0;

    virtual void setNumericField(int groupId, int fieldId, double value) = 0;
    virtual void setButtonField(int groupId, int fieldId, bool value) = 0;
    virtual void setMCfield(int groupId, int fieldId, int value) = 0;
    virtual void setRGBfield(int groupId, int fieldId, int R, int G, int B) = 0;
    virtual void setTextField(int groupId, int fieldId, String value) = 0;

    virtual double getNumericFieldInComplexGroupValue(int groupId, int stateId, int fieldId) = 0;
    virtual String getTextFieldValueInComplexGroupValue(int groupId, int stateId, int fieldId) = 0;
    virtual bool getButtonFieldValueInComplexGroupValue(int groupId, int stateId, int fieldId) = 0;
    virtual int getMCFieldValueInComplexGroupValue(int groupId, int stateId, int fieldId) = 0;
    virtual RGB getRGBFieldValueInComplexGroupValue(int groupId, int stateId, int fieldId) = 0;

    virtual void setNumericFieldInComplexGroupValue(int groupId, int stateId, int fieldId, double value) = 0;
    virtual void setButtonFieldInComplexGroupValue(int groupId, int stateId, int fieldId, bool value) = 0;
    virtual void setMCfieldInComplexGroupValue(int groupId, int stateId, int fieldId, int value) = 0;
    virtual void setRGBfieldInComplexGroupValue(int groupId, int stateId, int fieldId, int R, int G, int B) = 0;
    virtual void setTextFieldInComplexGroupValue(int groupId, int stateId, int fieldId, String value) = 0;

    virtual void setComplexGroupState(int groupId, int stateId) = 0;
};

#endif