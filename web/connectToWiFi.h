#include <WiFi.h>
#include <AsyncTCP.h>

#include "WifiCreds.h"

class WiFistate
{
private:
    WiFiClass myWiFi;

public:
    void connectToWifi()
    {
        WiFi.begin(ssid, password);

        while (WiFi.status() != WL_CONNECTED)
        {
            delay(1000);
            Serial.println("qqConnecting to WiFi..");
        }

        // Print ESP Local IP Address
        Serial.println(WiFi.localIP());
    }

    bool checkConnection()
    {
        return true;
    }
};
