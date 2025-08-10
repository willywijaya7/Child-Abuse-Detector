#include "GPSHandler.h"
#include <TinyGPSPlus.h>
#include <HardwareSerial.h>

#define RXD2 34  // GPS TX ke GPIO34
#define TXD2 35  // GPS RX ke GPIO35 (biasanya tidak dipakai)

HardwareSerial gpsSerial(1);  // UART1 (0 = USB, 1 & 2 bisa kita pakai)
TinyGPSPlus gps;

void initGPS() {
  gpsSerial.begin(9600, SERIAL_8N1, RXD2, TXD2);
}

GPSData getGPSData() {
  GPSData result = {NAN, NAN};
  unsigned long start = millis();
  while (millis() - start < 3000) {
    while (gpsSerial.available()) {
      gps.encode(gpsSerial.read());
    }
  }

  if (gps.location.isValid()) {
    result.latitude = gps.location.lat();
    result.longitude = gps.location.lng();
  }

  return result;
}
