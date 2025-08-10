#include <Arduino.h>
#include <Wire.h>
#include "MPU6050Handler.h"
#include "MAX30100Handler.h"
#include "JSONBuilder.h"
#include "WifiHelper.h"
#include "HTTPHelper.h"

// HAPUS
WiFiHelper wifi("rayawifi", "dotdotdotdot");

// Time tracking
unsigned long lastSampleTime = 0;
const int sampleInterval = 50;
const int samplesPerBatch = 20;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // SDA, SCL (default, tapi kita paksa ulang)
  delay(100);

  wifi.connect();
  delay(500);
  
  initMPU();
  initMAX30100();
}

void loop() {
  unsigned long now = millis();
  updateHeartRate(now);

  if (now - lastSampleTime >= sampleInterval) {
    lastSampleTime = now;
    String mpuBuffer;
    int sampleCount;
    
    if (readMPU(mpuBuffer, sampleCount, samplesPerBatch)) {
      HeartRateData hr = getHeartData();
      String payload = buildJSON(mpuBuffer, hr);
      Serial.print(payload);
      bool sukses = kirimPesanKeServer("https://03a04e78c64d.ngrok-free.app/datas/", payload);
      if (sukses) {
        Serial.println("Pesan berhasil dikirim.");
      } else {
        Serial.println("Gagal mengirim pesan.");
      }

      resetMPUBuffer();
    }
  }
}
