#ifndef MAX30100_HANDLER_H
#define MAX30100_HANDLER_H

struct HeartRateData {
  float heartRate;
  float spO2;
};

void initMAX30100();
void updateHeartRate(unsigned long now);
HeartRateData getHeartData();

#endif
