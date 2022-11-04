#ifndef WS_H
#define WS_H

#include "esp_websocket_client.h"

typedef struct wSConnection
{
    bool main;
    bool active;
    long timeConnected; // millis
    esp_websocket_client_handle_t handle;
} WSConnection;

class WS
{
private:
    String basicLink = "wss://devcontrol-backend-proba1.onrender.com/";
    esp_websocket_client_handle_t handle;
    WSConnection connections;

public:
    bool connectToWS()
    {
        const esp_websocket_client_config_t ws_cfg = {
            .uri = basicLink.c_str(),
        };
        handle = esp_websocket_client_init(&ws_cfg);
        esp_err_t x = esp_websocket_client_start(handle);
        while (esp_websocket_client_is_connected(handle) == false)
            ;
    }

    bool isConnected()
    {
        return esp_websocket_client_is_connected(handle);
    }
};

#endif