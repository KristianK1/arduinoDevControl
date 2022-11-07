#ifndef WS_H
#define WS_H

#include "esp_websocket_client.h"

typedef struct wSSConnectMessage
{
    String messageType;
    WSSDeviceConnectRequest data;
} WSSConnectMessage;

typedef struct wSSDeviceConnectRequest
{
    String deviceKey;
} WSSDeviceConnectRequest;

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
    esp_websocket_client_handle_t handle;
    WSSConnection *connection;

public:
    bool connectAndMaintainConnection()
    {
        if (connection == NULL)
        {
            connection = (WSSConnection *)calloc(1, sizeof(WSSConnection));
            connectToWS(connection);
        }
        else
        {
            if (millis() - connection->timeConnected > 0.5 * 60 * 1000)
            {
                if (connection->nextConnection == NULL)
                {
                    connection->nextConnection = (WSSConnection *)calloc(1, sizeof(WSSConnection));
                    bool connected = connectToWS(connection->nextConnection);
                    if (connected)
                    {
                        disconnectWS(*connection);
                        connection = connection->nextConnection;
                    }
                }
            }
        }
    }

    bool connectToWS(WSSConnection *newConn)
    {
        const esp_websocket_client_config_t ws_cfg = {
            .uri = basicLink.c_str(),
        };
        esp_websocket_client_handle_t newHandle = esp_websocket_client_init(&ws_cfg);
        esp_err_t x = esp_websocket_client_start(newHandle);
        while (esp_websocket_client_is_connected(newHandle) == false)
        {
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
        return esp_websocket_client_is_connected(handle);
    }
};

#endif