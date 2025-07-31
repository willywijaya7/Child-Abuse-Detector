#include "SIMHandler.h"
#include <SoftwareSerial.h>
#include "SIM800L.h"

#define RXD2 16
#define TXD2 17
#define SIM800_RST_PIN 5
const char APN[] = "internet";
const char URL[] = "http://202.74.74.49:5000/api";
const char CONTENT_TYPE[] = "application/json";

SoftwareSerial simSerial(RXD2, TXD2);
SIM800L* sim800l;

void initSIM() {
  simSerial.begin(9600);
  sim800l = new SIM800L((Stream *)&simSerial, SIM800_RST_PIN, 200, 512);

  while (!sim800l->isReady()) delay(1000);
  while (sim800l->getSignal() <= 0) delay(1000);
  while (sim800l->getRegistrationStatus() != REGISTERED_HOME &&
         sim800l->getRegistrationStatus() != REGISTERED_ROAMING) delay(1000);
  while (!sim800l->setupGPRS(APN)) delay(3000);
}

void sendData(const String& payload) {
  if (!sim800l->connectGPRS()) {
    sim800l->reset();
    initSIM();
    return;
  }

  uint16_t rc = sim800l->doPost(URL, CONTENT_TYPE, payload.c_str(), 10000, 10000);
  if (rc == 200) {
    Serial.println("POST Success:");
    Serial.println(sim800l->getDataReceived());
  } else {
    Serial.print("POST Failed: ");
    Serial.println(rc);
  }

  sim800l->disconnectGPRS();
}
