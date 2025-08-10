#include "WifiHelper.h"

WiFiHelper::WiFiHelper(const char* ssid, const char* password) {
    _SSID = ssid;
    _PASSWORD = password;
}

void WiFiHelper::connect() {
    Serial.print("Menghubungkan ke WiFi: ");
    Serial.println(_SSID);

    WiFi.begin(_SSID, _PASSWORD);
    int attempt = 0;

    while (WiFi.status() != WL_CONNECTED && attempt < 20) {
        delay(500);
        Serial.print(".");
        attempt++;
    }

    Serial.println();
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("WiFi terhubung!");
        // Serial.print("IP Address: ");
        // Serial.println(WiFi.localIP());
    } else {
        Serial.println("Gagal terhubung ke WiFi.");
    }
}

bool WiFiHelper::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

bool WiFiHelper::testInternetConnection(const char* serverURL, const int port) {
    WiFiClient client;
    Serial.print("Menghubungi ");
    Serial.print(serverURL);

    if (!client.connect(serverURL, port)) {
        Serial.println(" Gagal.");
        return false;
    }

    Serial.println(" Berhasil!");
    client.stop();
    return true;
}

IPAddress WiFiHelper::getIP() {
    return WiFi.localIP();
}
