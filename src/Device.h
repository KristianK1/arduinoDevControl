#ifndef DEVICE_H
#define DEVICE_H

#include "web\WifiConnection\WifiState.h"
#include "web\APIrequests\HTTP.h"
#include "web\WSSConnection\WS.h"
#include "IO_Config/IO.h"

class Device : public WiFistate, HTTP, WS, IO
{
private:
    int tempTimer = millis();

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
            // if (millis() - tempTimer > 10000)
            // {
            //     Serial.println("post");
            //     tempTimer = millis();
            //     HTTPresult result = HTTP::post("API/userAuth/register", "{\"username\":\"esp32_BBB\",\"password\":\"esp32\",\"email\":\"emaill\"}");
            //     if (result.success)
            //     {
            //         Serial.println(result.payload);
            //     }
            // }
            WS::connectAndMaintainConnection();
        }

        delay(500);
        test();
        delay(60 * 1000);
    }
};

#endif