#include <Arduino.h>
#include "MPUHandler.h"
#include "Configuration.h"
#include "WifiHelper.h"
#include "HTTPHelper.h"
#include "generateSensorDataToJson.h"

WiFiHelper wifi(SSID, PASSWORD);

void setup() {
  Serial.begin(115200); 
  delay(1000);
  const String& PESAN = generateSensorDataToJson(
    93.3, 97,              // HR, SpO2
    "TESTING",
    110.123456, -7.123456  // GPS lon, lat
  );
  wifi.connect();
  if (wifi.isConnected()) {
    if (wifi.testInternetConnection(SERVER_URL, 443)) {
      Serial.println("Terhubung ke Server");
      bool sukses = kirimPesanKeServer(SERVER_POST, PESAN);
      if (sukses) {
        Serial.println("Pesan berhasil dikirim.");
      } else {
        Serial.println("Gagal mengirim pesan.");
      }
    } else {
      Serial.println("Tidak Terhubung ke Server");
    }
  }
  initMPU();
}

void loop() {
  static unsigned long lastSample = 0;
  if (millis() - lastSample >= 50) {
    lastSample = millis();
    String mpuBatch = readFlattenedMPU();
    if (mpuBatch.length() > 0) {
      String payload = generateSensorDataToJson(
        93,
        93,
        mpuBatch,
        100,
        100
      );
      bool sukses = kirimPesanKeServer(SERVER_POST, payload);
      if (sukses) {
        Serial.println("Pesan berhasil dikirim.");
      } else {
        Serial.println("Gagal mengirim pesan.");
      }
    }
  }
}