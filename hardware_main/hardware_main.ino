#include <Arduino.h>
#include "WifiHelper.h"
#include "HTTPHelper.h"

const char* SSID = "";
const char* PASSWORD = "";
const char* SERVER_URL = "";

WiFiHelper wifi(SSID, PASSWORD);

void setup() {
  Serial.begin(115200);
  delay(1000);

  wifi.connect();
  if (wifi.isConnected()) {
    if (wifi.testInternetConnection("", 8000)) {
      Serial.println("Terhubung ke Server");
      bool sukses = kirimPesanKeServer(SERVER_URL, "Halo dari ESP32!");
      if (sukses) {
        Serial.println("Pesan berhasil dikirim.");
      } else {
        Serial.println("Gagal mengirim pesan.");
      }
    } else {
      Serial.println("Tidak Terhubung ke Server");
    }
  }

}

void loop() {
}
