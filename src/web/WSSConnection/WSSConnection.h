#ifndef WSS_CONNECTION_H
#define WSS_CONNECTION_H

#include "../../deviceKey.h"
#include "esp_websocket_client.h"
#include "ArduinoJson.h"

class WSSConnection
{
    private:
    long timeConnected = 0; // millis

    void sendfirstWSSMessage(){
        DynamicJsonDocument doc(1024);
        doc["messageType"] = "connectDevice";
        doc["data"]["deviceKey"] = deviceKey;
        String myString;
        serializeJson(doc, myString);
        Serial.println(myString);
        sendMessage(myString);
    }

    void sendMessage(String data){
        esp_websocket_client_send_text(handle, data.c_str(), data.length(), 5000);
    }

    public:
    esp_websocket_client_handle_t handle;

    bool isConnected(){
        return esp_websocket_client_is_connected(handle);
    }

    bool connectToWS() {
        esp_err_t x = esp_websocket_client_start(handle);
        int startedConnect = millis();
        while (esp_websocket_client_is_connected(handle) == false && millis() - startedConnect < 20000)
        {
            delay(500);
            Serial.println("connecting to WSS");
        }
        if (esp_websocket_client_is_connected(handle) == false)
        {
            Serial.println("failed to connect");
            return false;
        }
        Serial.println("not failed???");

        timeConnected = millis();
        Serial.println("not failed???2");
        sendfirstWSSMessage();
        return true;
    }

    void disconnect(){
        esp_websocket_client_stop(handle);
    }

};

#endif