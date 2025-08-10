
#include "MPU6050Handler.h"

Adafruit_MPU6050 mpu;
String flattenedMPU = "";
int sampleCount = 0;

void initMPU() {
  if (!mpu.begin()) {
    Serial.println("MPU6050 init FAILED");
    while (true);
  }
  Serial.println("MPU6050 ready");
}

bool readMPU(String &buffer, int &count, const int maxSamples) {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  flattenedMPU += String(a.acceleration.x, 3) + "," +
                  String(a.acceleration.y, 3) + "," +
                  String(a.acceleration.z, 3) + "," +
                  String(g.gyro.x, 3) + "," +
                  String(g.gyro.y, 3) + "," +
                  String(g.gyro.z, 3);

  sampleCount++;
  if (sampleCount < maxSamples) {
    flattenedMPU += ",";
  }

  buffer = flattenedMPU;
  count = sampleCount;
  return sampleCount >= maxSamples;
}

void resetMPUBuffer() {
  flattenedMPU = "";
  sampleCount = 0;
}
