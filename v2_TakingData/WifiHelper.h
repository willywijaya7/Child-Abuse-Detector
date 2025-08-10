#ifndef WIFIHELPER_H
#define WIFIHELPER_H

#include <WiFi.h>

class WiFiHelper {
public:
    WiFiHelper(const char* ssid, const char* password);
    void connect();
    bool isConnected();
    bool testInternetConnection(const char* serverURL,const int port);
    IPAddress getIP();

private:
    const char* _SSID;
    const char* _PASSWORD;
};

#endif
