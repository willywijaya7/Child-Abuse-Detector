#include "MAX30100Handler.h"
#include <Arduino.h>
#include <MAX30100_PulseOximeter.h>

PulseOximeter pox;
float lastHeartRate = 0;
float lastSpO2 = 0;
unsigned long lastHeartRateUpdate = 0;
const int heartRateUpdateInterval = 1000;

void initMAX30100() {
  if (!pox.begin()) {
    Serial.println("MAX30100 init FAILED");
  } else {
    Serial.println("MAX30100 ready");
  }
}

void updateHeartRate(unsigned long now) {
  pox.update();
  if (now - lastHeartRateUpdate >= heartRateUpdateInterval) {
    lastHeartRate = pox.getHeartRate();
    lastSpO2 = pox.getSpO2();
    lastHeartRateUpdate = now;
  }
}

HeartRateData getHeartData() {
  HeartRateData data;
  if (lastHeartRate > 0 && lastHeartRate < 200 && lastSpO2 > 0 && lastSpO2 <= 100) {
    data.heartRate = lastHeartRate;
    data.spO2 = lastSpO2;
  } else {
    data.heartRate = -1;
    data.spO2 = -1;
  }
  return data;
}
