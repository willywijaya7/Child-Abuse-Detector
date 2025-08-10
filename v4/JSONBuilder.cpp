
#include "JSONBuilder.h"
#include <ArduinoJson.h>

String buildJSON(const String &mpuData, const HeartRateData &hr) {
  DynamicJsonDocument doc(1024);

  JsonObject heart = doc.createNestedObject("max30100");
  heart["heartrate"] = hr.heartRate;
  heart["spO2"] = hr.spO2;

  doc["mpu6050"] = mpuData;

  JsonObject gpsJson = doc.createNestedObject("gt-u7");
  gpsJson["longitude"] = -1;
  gpsJson["latitude"] = -1;

  String output;
  serializeJson(doc, output);
  return output;
}
