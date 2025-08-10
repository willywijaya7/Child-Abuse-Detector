#include "HTTPHelper.h"
#include <WiFi.h>
#include <HTTPClient.h>

bool kirimPesanKeServer(const String& serverURL, const String& pesan) {
  HTTPClient http;
  http.begin(serverURL);
  http.addHeader("Content-Type", "application/json");

  int httpResponseCode = http.POST(pesan);

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
