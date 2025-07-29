#include "generateSensorDataToJson.h"
#include <Arduino.h>

String generateSensorDataToJson(
  float heartrate, float spO2, const String& mpu6050, 
  float longitude, float latitude
) {
  String PESAN = "{";
  PESAN += "\"max30100\":{\"heartrate\":" + String(heartrate) + ",\"spO2\":" + String(spO2) + "},";
  PESAN += "\"mpu6050\":\"" + mpu6050 + "\",";
  PESAN += "\"gt-u7\":{\"longitude\":" + String(longitude) + ",\"latitude\":" + String(latitude) + "}";
  PESAN += "}";

  return PESAN;
}