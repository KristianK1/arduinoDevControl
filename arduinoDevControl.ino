#include "src/Device.h"

Device myDevice;

void setup(){ 
    Serial.begin(115200);   
    myDevice.setup(); 
}

void loop(){
    myDevice.loop();
}