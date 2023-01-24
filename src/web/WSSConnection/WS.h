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


String newDataBuffer = "";  //""buffer""

static String newMessageHolder = "";
class WS
{
private:
    String basicLink = "wss://devcontrol-backend.onrender.com/";
    // String basicLink = "wss://devcontrol.herokuapp.com/";
    // String basicLink = "ws://192.168.1.239:8000";
    
    WSSConnection *connection;
    int messagesLastChecked = 0;
    int messageCheckInterval = 500;
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
            if (millis() - connection->timeConnected > 4.8 * 60 * 1000) // set to 4.99 mins later
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
        esp_websocket_client_config_t ws_cfg = {
            .uri = basicLink.c_str(),
        };
        ws_cfg.buffer_size = 10000;
        esp_websocket_client_handle_t newHandle = esp_websocket_client_init(&ws_cfg);
        esp_websocket_register_events(newHandle, WEBSOCKET_EVENT_DATA, websocket_event_handler, (void *)newHandle);
        esp_err_t x = esp_websocket_client_start(newHandle);
        int startedConnect = millis();
        while (esp_websocket_client_is_connected(newHandle) == false && millis() - startedConnect < 10000)
        {
            delay(100);
            // Serial.println("connecting to WSS");
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
        
        // if(millis() - messagesLastChecked > messageCheckInterval){
        //     connection->handle;
        // }

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
                Serial.println(data->op_code);
                Serial.println(data->payload_offset);
                newData = (char *)(data->data_ptr);
                // Serial.println("Received=%.*s", data->data_len, (char *)data->data_ptr);
                newData = newData.substring(0, data ->payload_len);
                Serial.println(newData.c_str());
                newDataBuffer = newData.c_str();
                newData = "";
                Serial.println("result");
                Serial.println(newDataBuffer.c_str());
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