#ifndef GPSHANDLER_H
#define GPSHANDLER_H

struct GPSData {
  float latitude;
  float longitude;
};

void initGPS();
GPSData getGPSData();

#endif
