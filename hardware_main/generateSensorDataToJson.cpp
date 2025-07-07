#include "generateSensorDataToJson.h"
#include <Arduino.h>

String generateSensorDataToJson(
  const String& timestamp,
  float heartrate, int spO2,
  float gyroX, float gyroY, float gyroZ,
  float accX, float accY, float accZ,
  float longitude, float latitude
) {
  String PESAN = "{";
  PESAN += "\"timestamp\":\"" + timestamp + "\",";
  PESAN += "\"max30100\":{\"heartrate\":" + String(heartrate) + ",\"spO2\":" + String(spO2) + "},";
  PESAN += "\"mpu6050\":{";
  PESAN += "\"gyroscope\":{\"x\":" + String(gyroX) + ",\"y\":" + String(gyroY) + ",\"z\":" + String(gyroZ) + "},";
  PESAN += "\"accelerometer\":{\"x\":" + String(accX) + ",\"y\":" + String(accY) + ",\"z\":" + String(accZ) + "}";
  PESAN += "},";
  PESAN += "\"gt-u7\":{\"longitude\":" + String(longitude) + ",\"latitude\":" + String(latitude) + "}";
  PESAN += "}";

  return PESAN;
}