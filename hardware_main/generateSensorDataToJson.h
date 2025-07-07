#ifndef GENERATESENSORDATATOJSON_H
#define GENERATESENSORDATATOJSON_H
#include <Arduino.h>

String generateSensorDataToJson (
  const String& timestamp,
  float heartrate, int spO2,
  float gyroX, float gyroY, float gyroZ,
  float accX, float accY, float accZ,
  float longitude, float latitude
);

#endif
