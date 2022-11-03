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

    bool post(char *link, char *body)
    {
    }
};

#endif