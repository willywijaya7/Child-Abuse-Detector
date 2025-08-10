

TinyGPSPlus gps;  // Buat objek GPS


GPSData getGPSData() {
  GPSData result = {NAN, NAN};

  // Baca data dari GPS selama 1 detik (non-blocking)
  unsigned long start = millis();
  while (millis() - start < 3000) {
    while (gpsSerial.available()) {
      gps.encode(gpsSerial.read());
    }
  }

  // Jika GPS sudah dapat sinyal (data valid)
  if (gps.location.isValid()) {
    result.latitude = gps.location.lat();
    result.longitude = gps.location.lng();
  }

  return result;
}
