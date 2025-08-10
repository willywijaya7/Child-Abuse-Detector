#ifndef GENERATESENSORDATATOJSON_H
#define GENERATESENSORDATATOJSON_H
#include <Arduino.h>

String generateSensorDataToJson (
  float heartrate, float spO2, const String& mpu6060, 
  float longitude, float latitude
);

#endif
