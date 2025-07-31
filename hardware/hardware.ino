#include "MPUHandler.h"
#include "GPSHandler.h"
#include "SIMHandler.h"
#include "BPMHandler.h"
#include <ArduinoJson.h>

void setup() {
  Serial.begin(115200);
  delay(2000);

  initSIM();
  initGPS();
  initMPU();
  initMAX30100();
}

void loop() {
  static unsigned long lastSample = 0;
  if (millis() - lastSample >= 50) {
    lastSample = millis();
    String mpuBatch = readFlattenedMPU();
    if (mpuBatch.length() > 0) {
      GPSData gps = getGPSData();
      MAX30100Data maxData = readMAX30100();  // ← Baca data dari sensor MAX30100

      DynamicJsonDocument doc(2048);
      doc["mpu6050"] = mpuBatch;

      JsonObject gpsJson = doc.createNestedObject("gt-u7");
      gpsJson["longitude"] = isnan(gps.longitude) ? 0 : gps.longitude;
      gpsJson["latitude"] = isnan(gps.latitude) ? 0 : gps.latitude;

      JsonObject max30100 = doc.createNestedObject("max30100");
      max30100["heartrate"] = maxData.heartrate;
      max30100["spO2"] = maxData.spO2;

      String payload;
      serializeJson(doc, payload);
      sendData(payload);
    }
  }
}
