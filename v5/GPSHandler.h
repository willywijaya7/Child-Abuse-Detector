#ifndef GPS_HANDLER_H
#define GPS_HANDLER_H

#include <TinyGPSPlus.h>

// Struktur data untuk menyimpan data GPS
struct GPSData {
  double latitude;
  double longitude;
};

// Inisialisasi GPS
void initGPS();

// Fungsi untuk mendapatkan data lokasi (latitude & longitude)
GPSData getGPSData();

#endif
