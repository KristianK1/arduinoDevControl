#ifndef WS_H
#define WS_H

#include "../../deviceKey.h"
#include "esp_websocket_client.h"
#include "ArduinoJson.h"

#define WS_MAXTIME 300000
#define WS_RECONNECT_TIME 30000
typedef struct wSSConnection
{
    long timeConnected; // millis
    esp_websocket_client_handle_t handle;

    bool isConnected(){
        return esp_websocket_client_is_connected(handle);
    }

    int getRemainingTime(){
        if(isConnected()){
            return WS_MAXTIME - millis() + timeConnected;
        }
        return -1;
    }

} WSSConnection;


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

    WS(){
        connection1.handle = createWsHandle();
        connection2.handle = createWsHandle();
    }

    esp_websocket_client_handle_t createWsHandle(){

        esp_websocket_client_config_t ws_cfg = {
            .uri = basicLink.c_str(),
        };
        ws_cfg.buffer_size = 10000;
    
        esp_websocket_client_handle_t handle = esp_websocket_client_init(&ws_cfg);
        esp_websocket_register_events(handle, WEBSOCKET_EVENT_DATA, websocket_event_handler, (void *)(handle));
        return handle;    
    }

    bool connectToWS(WSSConnection &conn) {
        esp_err_t x = esp_websocket_client_start(conn.handle);
        int startedConnect = millis();
        while (esp_websocket_client_is_connected(conn.handle) == false && millis() - startedConnect < 10000)
        {
            delay(500);
            Serial.println("connecting to WSS");
        }
        if (esp_websocket_client_is_connected(conn.handle) == false)
        {
            Serial.println("failed to connect");
            return false;
        }
        Serial.println("not failed???");

        conn.timeConnected = millis();
        Serial.println("not failed???2");
        sendfirstWSSMessage(conn);
        return true;
    }
public:

    bool connectAndMaintainConnection()
    {
        if(connection1.getRemainingTime() > 30000){
            return true;
        }
        else if(connection2.getRemainingTime() > 30000){
            return true;
        }


    }

    void sendfirstWSSMessage(WSSConnection conn)
    {
        DynamicJsonDocument doc(1024);
        doc["messageType"] = "connectDevice";
        doc["data"]["deviceKey"] = deviceKey;
        String myString;
        serializeJson(doc, myString);
        Serial.println(myString);
        sendMessage(conn, myString);
    }

    void sendMessage(WSSConnection conn, String data)
    {
        esp_websocket_client_send_text(conn.handle, data.c_str(), data.length(), 5000);
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
                // Serial.println(data->op_code);
                // Serial.println(data->payload_offset);
                newData = (char *)(data->data_ptr);
                // Serial.println("Received=%.*s", data->data_len, (char *)data->data_ptr);
                newData = newData.substring(0, data ->payload_len);
                // Serial.println(newData.c_str());
                newDataBuffer = newData.c_str();
                newData = "";
                Serial.println("result");
                // Serial.println(newDataBuffer.c_str());
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