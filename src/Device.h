#ifndef DEVICE_H
#define DEVICE_H

#include "web\WifiConnection\WifiState.h"
#include "web\APIrequests\HTTP.h"
#include "web\WSSConnection\WS.h"
#include "IO_Config\IO.h"

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


    void setup(){
        
        bool wifiConn = WiFistate::keepConnectionAlive();

        while(WiFistate::checkConnection() == false) {}
        WS::connectAndMaintainConnection();
        delay(500);
        IO::setupFields();
        registerDevice();
    }
    void loop()
    {
        bool wifiConn = WiFistate::keepConnectionAlive();
        digitalWrite(2, wifiConn);
        if (wifiConn)
        {
            WS::connectAndMaintainConnection();
            



        }
    }

    void registerDevice()
    {
        String data = IO::getTotalDeviceString();
        Serial.println(data);
        HTTP::post("API/device/registerDeviceData", data);
    }
};

#endif