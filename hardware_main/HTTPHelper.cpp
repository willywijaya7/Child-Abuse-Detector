#include "HTTPHelper.h"
#include <WiFi.h>
#include <HTTPClient.h>

bool kirimPesanKeServer(const char* serverURL, const String& pesan) {
  HTTPClient http;
  http.begin(serverURL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  String httpRequestData = "pesan=" + pesan;
  int httpResponseCode = http.POST(httpRequestData);

  if (httpResponseCode > 0) {
      Serial.print("Response: ");
      Serial.println(http.getString());
  } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
  }

  http.end();
  return httpResponseCode > 0;
}
