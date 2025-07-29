#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include "Configuration.h"
#include "WifiHelper.h"
#include "HTTPHelper.h"
#include "generateSensorDataToJson.h"

String flattenedMPU = "";
int sampleCount = 0;
const int samplesPerBatch = 20;
unsigned long lastSampleTime = 0;
const int sampleInterval = 50; // 20 Hz
Adafruit_MPU6050 mpu;

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

  if (!mpu.begin()) {
    Serial.println("Failed to initialize MPU6050");
    while (1);
  }
  Serial.println("MPU6050 connected");
}

void loop() 
{
  if (wifi.isConnected()) 
  {
    unsigned long now = millis();
    if (now - lastSampleTime >= sampleInterval) 
    {
      lastSampleTime = now;

      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);

      flattenedMPU += String(a.acceleration.x, 3) + "," +
                      String(a.acceleration.y, 3) + "," +
                      String(a.acceleration.z, 3) + "," +
                      String(g.gyro.x, 3) + "," +
                      String(g.gyro.y, 3) + "," +
                      String(g.gyro.z, 3);

      sampleCount++;

      if (sampleCount < samplesPerBatch) 
      {
        flattenedMPU += ",";
      }

      // Setelah 20 sampel (1 detik)
      if (sampleCount >= samplesPerBatch) 
      {
        const String& PESAN = generateSensorDataToJson(
          93.3, 97,              // HR, SpO2
          flattenedMPU,
          110.123456, -7.123456  // GPS lon, lat
        );
        bool sukses = kirimPesanKeServer(SERVER_POST, PESAN);
        if (sukses) {
          Serial.println("Pesan berhasil dikirim.");
        } else {
          Serial.println("Gagal mengirim pesan.");
        }
      }
    }
  }
}