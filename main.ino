#include "src/Device.h"

Device myDevice;

void setup(){
<<<<<<< Updated upstream
    pinMode(2, OUTPUT);
    Serial.begin(115200);    
=======
    pinMode(23, OUTPUT);
    Serial.begin(115200);   
    myDevice.setup(); 
>>>>>>> Stashed changes
}

void loop(){
    myDevice.loop();
}