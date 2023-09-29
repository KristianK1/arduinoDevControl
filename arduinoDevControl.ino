#include "src/Device.h"

Device myDevice;

void setup(){ 
    pinMode(23, OUTPUT);
    Serial.begin(115200);   
    myDevice.setup(); 
}

void loop(){
    myDevice.loop();
}