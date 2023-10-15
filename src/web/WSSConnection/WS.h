#ifndef WS_H
#define WS_H

#include "../../deviceKey.h"
#include "esp_websocket_client.h"
#include "ArduinoJson.h"
#include "WSSConnection.h"
#include "../serverLink/serverLink.h"

String newDataBuffer = "";  //""buffer""
static String newMessageHolder = "";

class WS: ServerLink
{
private:
    
    WSSConnection connection;
    
    int messagesLastChecked = 0;
    int messageCheckInterval = 500;

    esp_websocket_client_handle_t createWsHandle(){

        esp_websocket_client_config_t ws_cfg = {
            .uri = wsLink.c_str(),
        };
        ws_cfg.buffer_size = 10000;
    
        esp_websocket_client_handle_t handle = esp_websocket_client_init(&ws_cfg);
        esp_websocket_register_events(handle, WEBSOCKET_EVENT_DATA, websocket_event_handler, (void *)(handle));
        return handle;    
    }
public:
    
    WS(){
        connection.handle = createWsHandle();
    }

    bool connectAndMaintainConnection()
    {
        if(connection.isConnected()) return true;
        return connection.connectToWS();
    }

    static void websocket_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
    {
        esp_websocket_event_data_t *data = (esp_websocket_event_data_t *)event_data;
        
        String newData;
        switch (event_id) {
            case WEBSOCKET_EVENT_CONNECTED:
                Serial.println("WEBSOCKET_EVENT_CONNECTED");
                break;
            case WEBSOCKET_EVENT_DISCONNECTED:
                Serial.println("WEBSOCKET_EVENT_DISCONNECTED");
                break;
            case WEBSOCKET_EVENT_DATA:
                Serial.println("WEBSOCKET_EVENT_DATA");
                newData = (char *)(data->data_ptr);
                newData = newData.substring(0, data ->payload_len);
                newDataBuffer = newData.c_str();
                newData = "";
                Serial.print("result: |");
                Serial.print(newDataBuffer.c_str());
                Serial.println("|");
                newMessageHolder = newDataBuffer.c_str();
                break;
            case WEBSOCKET_EVENT_ERROR:
                Serial.println("WEBSOCKET_EVENT_ERROR");
                break;
            
            case WEBSOCKET_EVENT_MAX:
                Serial.println("WEBSOCKET_EVENT_MAX");
                break;
        }
    }
};

#endif