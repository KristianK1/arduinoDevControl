#ifndef WIFISTATE_H
#define WIFISTATE_H

#include <WiFi.h>
#include "WifiCreds.h"

// char *ssid = "xxxxxxxxxxxxx";
// char *password = "xxxxxxxxxxxxxxxx";

class WiFistate
{
private:
public:
    bool connectToWifi()
    {
        int connectTimeout = 8000;
        int startMillis = millis();
        WiFi.begin(ssid.c_str(), password.c_str());

        while (WiFi.status() != WL_CONNECTED)
        {
            if (millis() - startMillis > connectTimeout)
                break;
            delay(500);
            Serial.println("qqConnecting to WiFi..");
        }
        return WiFi.status() == WL_CONNECTED;
    }

    bool keepConnectionAlive()
    {
        bool connected = checkConnection();
        if (!connected)
        {
            connectToWifi();
        }
        return checkConnection();
    }

    bool checkConnection()
    {
        return WiFi.status() == WL_CONNECTED;
    }
};

#endif