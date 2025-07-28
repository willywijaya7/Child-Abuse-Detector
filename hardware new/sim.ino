void sendData(const String& jsonPayload) {
  bool connected = false;
  for (uint8_t i = 0; i < 5 && !connected; i++) {
    delay(1000);
    connected = sim800l->connectGPRS();
  }

  if (!connected) {
    Serial.println(F("GPRS not connected. Resetting..."));
    sim800l->reset();
    setupModule();
    return;
  }

  Serial.println(F("Sending HTTP POST..."));
  uint16_t rc = sim800l->doPost(URL, CONTENT_TYPE, jsonPayload.c_str(), 10000, 10000);

  if (rc == 200) {
    Serial.print(F("HTTP POST OK ("));
    Serial.print(sim800l->getDataSizeReceived());
    Serial.println(F(" bytes)"));
    Serial.print(F("Response: "));
    Serial.println(sim800l->getDataReceived());
  } else {
    Serial.print(F("HTTP POST failed: "));
    Serial.println(rc);
  }

  sim800l->disconnectGPRS();
  sim800l->setPowerMode(MINIMUM);
}

void setupModule() {
  while (!sim800l->isReady()) {
    Serial.println(F("Waiting for SIM800L..."));
    delay(1000);
  }

  uint8_t signal = sim800l->getSignal();
  while (signal <= 0) {
    Serial.println(F("Waiting for signal..."));
    delay(1000);
    signal = sim800l->getSignal();
  }

  Serial.print(F("Signal OK: "));
  Serial.println(signal);

  NetworkRegistration status = sim800l->getRegistrationStatus();
  while (status != REGISTERED_HOME && status != REGISTERED_ROAMING) {
    Serial.println(F("Waiting for network..."));
    delay(1000);
    status = sim800l->getRegistrationStatus();
  }

  Serial.println(F("Network OK"));

  bool gprs = sim800l->setupGPRS(APN);
  while (!gprs) {
    Serial.println(F("Retrying GPRS..."));
    delay(3000);
    gprs = sim800l->setupGPRS(APN);
  }

  Serial.println(F("GPRS setup complete"));
}