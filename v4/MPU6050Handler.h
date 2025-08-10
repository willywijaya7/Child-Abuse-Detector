
#ifndef MPU6050_HANDLER_H
#define MPU6050_HANDLER_H

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

void initMPU();
bool readMPU(String &buffer, int &count, const int maxSamples);
void resetMPUBuffer();

#endif
