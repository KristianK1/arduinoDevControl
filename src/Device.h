#ifndef DEVICE_H
#define DEVICE_H

#include "web/WifiConnection/WifiState.h"
#include "web/APIrequests/HTTP.h"

class Device : WiFistate, HTTP
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
            HTTPresult result = HTTP::get(String("API/device/1"));
            if (result.success)
            {
                // Serial.println(result.payload);
            }
            Serial.println((millis() - CurrMillis));
        }
        delay(5000);
    }
};

#endif