#ifndef DEVICE_H
#define DEVICE_H

#include "web/WifiConnection/WifiState.h"
#include "web/APIrequests/HTTP.h"
#include "web/WSSConnection/WS.h"

class Device : WiFistate, HTTP, WS
{
private:
public:
    Device()
    {
    }

    // virtual ~Device()
    // {
    //     // trebat ce nekad
    // }

    void loop()
    {
        bool wifiConn = WiFistate::keepConnectionAlive();
        digitalWrite(2, wifiConn);
        if (wifiConn)
        {
            int CurrMillis = millis();
            HTTPresult result = HTTP::post("API/userAuth/register", "{\"username\":\"esp32\",\"password\":\"esp32\",\"email\":\"emaill\"}");
            if (result.success)
            {
                Serial.println(result.payload);
            }
            Serial.println((millis() - CurrMillis));

            Serial.println("prije" + WS::isConnected());
            if (!WS::isConnected())
            {
                WS::connectToWS();
            }
            Serial.println("poslije" + WS::isConnected());
        }
        delay(5000);
    }
};

#endif