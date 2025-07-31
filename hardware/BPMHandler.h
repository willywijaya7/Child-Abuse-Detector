#ifndef BPMHANDLER_H
#define BPMHANDLER_H

struct MAX30100Data {
  float heartrate;
  float spO2;
};

void initMAX30100();
MAX30100Data readMAX30100();

#endif
