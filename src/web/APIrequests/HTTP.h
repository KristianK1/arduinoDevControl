#ifndef HTTP_H
#define HTTP_H

#include <HTTPClient.h>

typedef struct hTTPresult
{
    bool success;
    String payload;
    int statusCode;
} HTTPresult;

class HTTP
{
private:
    HTTPClient http;
    String basicLink = String("https://devcontrol-backend-proba1.onrender.com/");

public:
    HTTPresult get(String subLink)
    {
        HTTPresult result;
        String fullLink = basicLink + subLink;
        http.begin(fullLink.c_str());
        int responseCode = http.GET();
        String payload;
        if (responseCode > 0)
        {
            result.success = true;
            result.statusCode = responseCode;
            result.payload = http.getString();
        }
        else
        {
            result.success = false;
        }
        http.end();
        return result;
    }

    HTTPresult post(String sublink, String body)
    {
        HTTPresult result;
        String fullLink = basicLink + sublink;
        http.begin(fullLink.c_str());
        Serial.println("1");
        http.addHeader("Content-Type", "text/html; charset=utf-8");
        Serial.println("2");
        int responseCode = http.POST(body);
        Serial.println("3");

        // if (responseCode > 0)
        // {
            result.success = true;
            result.statusCode = responseCode;
            result.payload = http.getString();
        // }
        // else
        // {
        //     result.success = false;
        // }
        http.end();
        Serial.println("4");

        return result;
    }
};

#endif