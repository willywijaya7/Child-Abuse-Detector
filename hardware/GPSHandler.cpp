#include "GPSHandler.h"
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

#define RXD_GPS 34
#define TXD_GPS 35

TinyGPSPlus gps;
SoftwareSerial gpsSerial(RXD_GPS, TXD_GPS);

void initGPS() {
  gpsSerial.begin(9600);
}

GPSData getGPSData() {
  GPSData result = {NAN, NAN};
  unsigned long start = millis();
  while (millis() - start < 3000) {
    while (gpsSerial.available()) gps.encode(gpsSerial.read());
  }

  if (gps.location.isValid()) {
    result.latitude = gps.location.lat();
    result.longitude = gps.location.lng();
  }

  return result;
}
