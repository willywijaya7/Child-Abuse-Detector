#include <Arduino.h>
#include "WifiHelper.h"
#include "HTTPHelper.h"

const char* SSID = "rayawifi";
const char* PASSWORD = "dotdotdotdot";
const char* SERVER_URL = "http://192.168.1.7:8000/api/data/save";

WiFiHelper wifi(SSID, PASSWORD);

void setup() {
  Serial.begin(115200);
  delay(1000);

  wifi.connect();
  if (wifi.isConnected()) {
    if (wifi.testInternetConnection("192.168.1.7", 8000)) {
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
