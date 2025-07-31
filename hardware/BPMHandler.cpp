#include "BPMHandler.h"
#include <MAX30100_PulseOximeter.h>

#define REPORTING_PERIOD_MS     1000

PulseOximeter pox;
uint32_t tsLastReport = 0;
float lastHR = 0;
float lastSpO2 = 0;

void onBeatDetected() {
  // Optional: feedback saat detak jantung terdeteksi
}

void initMAX30100() {
  if (!pox.begin()) {
    Serial.println("MAX30100 init failed");
    return;
  }
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

MAX30100Data readMAX30100() {
  pox.update();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    tsLastReport = millis();
    lastHR = pox.getHeartRate();
    lastSpO2 = pox.getSpO2();
  }

  return {lastHR, lastSpO2};
}
