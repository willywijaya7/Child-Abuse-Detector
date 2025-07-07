#include <Arduino.h>
#include "Configuration.h"
#include "WifiHelper.h"
#include "HTTPHelper.h"
#include "generateSensorDataToJson.h"

WiFiHelper wifi(SSID, PASSWORD);

void setup() {
  Serial.begin(115200); 
  delay(1000);
  const String& PESAN = generateSensorDataToJson(
    "2025-07-07-14-00-00", // timestamp
    93.3, 97,              // HR, SpO2
    0.09, 0.05, 0.04,      // Gyro X, Y, Z
    0.09, 0.05, 0.04,      // Accel X, Y, Z
    110.123456, -7.123456  // GPS lon, lat
  );
  wifi.connect();
  if (wifi.isConnected()) {
    if (wifi.testInternetConnection("https://5c95-203-24-50-227.ngrok-free.app", 443)) {
      Serial.println("Terhubung ke Server");
      bool sukses = kirimPesanKeServer(SERVER_URL, PESAN);
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

void loop() 
{

}


