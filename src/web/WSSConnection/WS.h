#ifndef WS_H
#define WS_H

#include "../../deviceKey.h"
#include "esp_websocket_client.h"
#include "ArduinoJson.h"

typedef struct wSSDeviceConnectRequest
{
    String deviceKey;
} WSSDeviceConnectRequest;

typedef struct wSSFirstMessage
{
    String messageType;
    WSSDeviceConnectRequest data;
} WSSFirstMessage;

typedef struct wSSConnection
{
    long timeConnected; // millis
    esp_websocket_client_handle_t handle;
    wSSConnection *nextConnection;
} WSSConnection;

class WS
{
private:
    // String basicLink = "wss://devcontrol-backend-proba1.onrender.com/";
    String basicLink = "ws://192.168.1.103:8000";
    WSSConnection *connection;

public:
    bool connectAndMaintainConnection()
    {
        if (connection == NULL)
        {
            startFirstConnection();
        }
        else if (!isConnected())
        {
            startNextConnection();
        }
        else
        {
            if (millis() - connection->timeConnected > 0.5 * 60 * 1000) // set to 4.99 mins later
            {
                startNextConnection();
            }
        }
    }

    void startFirstConnection()
    {
        connection = (WSSConnection *)calloc(1, sizeof(WSSConnection));
        bool connected = connectToWS(connection);
        if (connected)
        {
            sendfirstWSSMessage(*connection);
        }
        else
        {
            delete (connection);
            connection = NULL;
        }
    }

    void startNextConnection()
    {
        connection->nextConnection = (WSSConnection *)calloc(1, sizeof(WSSConnection));
        bool connected = connectToWS(connection->nextConnection);
        if (connected)
        {
            sendfirstWSSMessage(*connection->nextConnection);
            disconnectWS(*connection);
            wSSConnection *connectionTemp = connection;
            connection = connection->nextConnection;
            delete (connectionTemp);
        }
        else
        {
            delete (connection->nextConnection);
        }
    }

    bool connectToWS(WSSConnection *newConn)
    {
        const esp_websocket_client_config_t ws_cfg = {
            .uri = basicLink.c_str(),
        };
        esp_websocket_client_handle_t newHandle = esp_websocket_client_init(&ws_cfg);
        esp_err_t x = esp_websocket_client_start(newHandle);
        int startedConnect = millis();
        while (esp_websocket_client_is_connected(newHandle) == false && millis() - startedConnect < 10000)
        {
            delay(100);
            Serial.println("connecting to WSS");
        }
        if (esp_websocket_client_is_connected(newHandle) == false)
        {
            Serial.println("failed to connect");
            return false;
        }
        WSSConnection newConnection;
        newConn->handle = newHandle;
        newConn->timeConnected = millis();
        newConn->nextConnection = NULL;
        return true;
    }

    void disconnectWS(WSSConnection conn)
    {
        esp_websocket_client_stop(conn.handle);
    }

    bool isConnected()
    {
        return esp_websocket_client_is_connected(connection->handle);
    }

    bool sendfirstWSSMessage(WSSConnection conn)
    {
        WSSFirstMessage message;
        message.messageType = "connectDevice";
        message.data.deviceKey = deviceKey;

        DynamicJsonDocument doc(1024);
        doc["messageType"] = message.messageType;
        doc["data"]["deviceKey"] = message.data.deviceKey;
        String myString;
        serializeJson(doc, myString);
        Serial.println(myString);
        sendMessage(conn, myString);
    }

    void sendMessage(WSSConnection conn, String data)
    {
        esp_websocket_client_send_text(conn.handle, data.c_str(), data.length(), 5000);
    }
};

#endif