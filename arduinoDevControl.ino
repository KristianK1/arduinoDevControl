#include "src/Device.h"

Device myDevice;

void setup(){ 
    Serial.begin(115200);   
   myDevice.setup(); 
}

void loop(){
    myDevice.loop();
//     Serial.println(digitalRead(34));
//   Serial.println(digitalRead(35));
//   Serial.println();
//   delay(10);
}