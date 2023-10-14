#ifndef WS_H
#define WS_H

#include "../../deviceKey.h"
#include "esp_websocket_client.h"
#include "ArduinoJson.h"
#include "WSSConnection.h"


String newDataBuffer = "";  //""buffer""
static String newMessageHolder = "";


class WS
{
private:
    String basicLink = "wss://devcontrol-backend.onrender.com/";
    // String basicLink = "wss://devcontrol.herokuapp.com/";
    // String basicLink = "ws://192.168.1.205:8000";
    
    WSSConnection connection1;
    WSSConnection connection2;
    
    int messagesLastChecked = 0;
    int messageCheckInterval = 500;

    esp_websocket_client_handle_t createWsHandle(){

        esp_websocket_client_config_t ws_cfg = {
            .uri = basicLink.c_str(),
        };
        ws_cfg.buffer_size = 10000;
    
        esp_websocket_client_handle_t handle = esp_websocket_client_init(&ws_cfg);
        esp_websocket_register_events(handle, WEBSOCKET_EVENT_DATA, websocket_event_handler, (void *)(handle));
        return handle;    
    }
public:
    
    WS(){
        connection1.handle = createWsHandle();
        connection2.handle = createWsHandle();
    }

    bool connectAndMaintainConnection()
    {
        int timeLeft1 = connection1.getRemainingTime();
        int timeLeft2 = connection2.getRemainingTime();

        if(timeLeft1 > WS_RECONNECT_TIME){
            String x = String("CONN_1 long time to reconnect\n") + String("time1: ") + String(timeLeft1) + String("\ntime2: ") + String(timeLeft2);
            Serial.println(x);
            return true;
        }
        else if(timeLeft2 > WS_RECONNECT_TIME){
            String x = String("CONN_2 long time to reconnect\n") + String("time1: ") + String(timeLeft1) + String("\ntime2: ") + String(timeLeft2);
            Serial.println(x);
            return true;
        }
        else{
            Serial.println("No conn has long time to reconnect\n");
            Serial.println("CONN1 time to recconect " + timeLeft1);
            Serial.println("CONN2 time to recconect " + timeLeft2);
            
            if(timeLeft1 > timeLeft2){           
                Serial.println("CONN2 reconnect");
                connection2.disconnect();
                delay(100);
                connection2.connectToWS();
            }
            else{
                Serial.println("CONN1 reconnect");
                connection1.disconnect();
                delay(100);
                connection1.connectToWS();
            }
        }
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