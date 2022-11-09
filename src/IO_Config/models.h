#ifndef WSS_IO_MODELS_H
#define WSS_IO_MODELS_H

typedef struct alterFieldValue
{
    int deviceId;
    int groupId;
    int fieldId;
    String fieldType;
} AlterFieldValue;


typedef struct alterComplexGroupState
{
    int deviceId;
    int groupId;
    String state;
} AlterComplexGroupState;

#endif