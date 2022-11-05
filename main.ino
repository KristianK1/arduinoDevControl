#include "src/Device.h"

Device myDevice;

void setup(){
    pinMode(2, OUTPUT);
    Serial.begin(115200);    
}

void loop(){
    myDevice.loop();
}