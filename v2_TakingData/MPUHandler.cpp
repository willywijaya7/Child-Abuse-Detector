#include "MPUHandler.h"

Adafruit_MPU6050 mpu;
String flattenedData;
int sampleCount = 0;
const int samplesPerBatch = 20;

void initMPU() {
  if (!mpu.begin()) {
    Serial.println("Failed to initialize MPU6050");
    while (1);
  }
  Serial.println("MPU6050 connected");
}

String readFlattenedMPU() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  flattenedData += String(a.acceleration.x, 3) + "," +
                   String(a.acceleration.y, 3) + "," +
                   String(a.acceleration.z, 3) + "," +
                   String(g.gyro.x, 3) + "," +
                   String(g.gyro.y, 3) + "," +
                   String(g.gyro.z, 3);

  sampleCount++;
  if (sampleCount < samplesPerBatch) flattenedData += ",";

  if (sampleCount >= samplesPerBatch) {
    String batch = flattenedData;
    flattenedData = "";
    sampleCount = 0;
    return batch;
  }

  return "";
}
