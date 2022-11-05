#ifndef WS_H
#define WS_H

#include "esp_websocket_client.h"

typedef struct wSConnection
{
    long timeConnected; // millis
    esp_websocket_client_handle_t handle;
    wSConnection *nextConnection;
} WSConnection;

class WS
{
private:
    // String basicLink = "wss://devcontrol-backend-proba1.onrender.com/";
    String basicLink = "ws://192.168.1.100:8000";
    
    esp_websocket_client_handle_t handle;
    WSConnection *connection;

public:
    bool connectAndMaintainConnection()
    {
        if (connection == NULL)
        {
            connection = (WSConnection *)calloc(1, sizeof(WSConnection));
            connectToWS(connection);
        }
        else
        {
            if (millis() - connection->timeConnected > 0.5 * 60 * 1000)
            {
                if (connection->nextConnection == NULL)
                {
                    connection->nextConnection = (WSConnection *)calloc(1, sizeof(WSConnection));
                    bool connected = connectToWS(connection->nextConnection);
                    if(connected){
                        disconnectWS(*connection);
                        connection = connection->nextConnection;
                    }
                }
            }
        }
    }

    bool connectToWS(WSConnection *newConn)
    {
        const esp_websocket_client_config_t ws_cfg = {
            .uri = basicLink.c_str(),
        };
        esp_websocket_client_handle_t newHandle = esp_websocket_client_init(&ws_cfg);
        esp_err_t x = esp_websocket_client_start(newHandle);
        while (esp_websocket_client_is_connected(newHandle) == false)
        {
        }
        WSConnection newConnection;
        newConn->handle = newHandle;
        newConn->timeConnected = millis();
        newConn->nextConnection = NULL;
        return true;
    }

    void disconnectWS(WSConnection conn){
        esp_websocket_client_stop(conn.handle);
    }

    bool isConnected()
    {
        return esp_websocket_client_is_connected(handle);
    }
};

#endif