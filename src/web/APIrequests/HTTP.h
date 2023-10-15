#ifndef HTTP_H
#define HTTP_H

#include <HTTPClient.h>
#include "../serverLink/serverLink.h"

typedef struct hTTPresult
{
    bool success;
    String payload;
    int statusCode;
} HTTPresult;

class HTTP: ServerLink
{
private:
    HTTPClient http;

public:
    HTTPresult get(String subLink)
    {
        HTTPresult result;
        String fullLink = httpLink + subLink;
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
        String fullLink = httpLink + sublink;
        http.begin(fullLink.c_str());
        http.addHeader("Content-Type", "application/json");
        int responseCode = http.POST(body);
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
};

#endif