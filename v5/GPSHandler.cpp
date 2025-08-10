#include "GPSHandler.h"
#include <HardwareSerial.h>

#define RXD_GPS 34
#define TXD_GPS 35

// Objek GPS dan Serial untuk ESP32 (gunakan UART1)
TinyGPSPlus gps;
HardwareSerial gpsSerial(1);  // UART1

// Fungsi inisialisasi GPS
void initGPS() {
  gpsSerial.begin(9600, SERIAL_8N1, RXD_GPS, TXD_GPS);
}

// Fungsi untuk membaca data GPS
GPSData getGPSData() {
  GPSData result = {NAN, NAN};

  unsigned long start = millis();
  while (millis() - start < 3000) {
    while (gpsSerial.available()) {
      char c = gpsSerial.read();
      gps.encode(c);
      Serial.write(c);  // Tampilkan NMEA sentence langsung
    }
  }

  if (gps.location.isValid()) {
    result.latitude = gps.location.lat();
    result.longitude = gps.location.lng();
    Serial.println("GPS VALID ✅");
  } else {
    Serial.println("GPS INVALID ❌");
  }

  return result;
}
