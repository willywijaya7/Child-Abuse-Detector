#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>
#include "SIM800L.h"
#include <ArduinoJson.h>

// Pin dan Konfigurasi
#define RXD2 16
#define TXD2 17
#define SIM800_RST_PIN 5

const char APN[] = "internet";
const char URL[] = "http://202.74.74.49:5000/api";
const char CONTENT_TYPE[] = "application/json";

SIM800L* sim800l;
SoftwareSerial simSerial(RXD2, TXD2);

// Sensor
Adafruit_MPU6050 mpu;

// GPS dummy
#define RXD_GPS 34
#define TXD_GPS 35
SoftwareSerial gpsSerial(RXD_GPS, TXD_GPS);

// Buffer data
String flattenedMPU = "";
int sampleCount = 0;
const int samplesPerBatch = 20;
unsigned long lastSampleTime = 0;
const int sampleInterval = 50; // 20 Hz

struct GPSData {
  float latitude;
  float longitude;
};


void setup() {
  Serial.begin(115200);
  delay(3000);
  simSerial.begin(9600);
  sim800l = new SIM800L((Stream *)&simSerial, SIM800_RST_PIN, 200, 512);
  setupModule();

  gpsSerial.begin(9600);

  // Init MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to initialize MPU6050");
    while (1);
  }
  Serial.println("MPU6050 connected");
}

void loop() {
  unsigned long now = millis();

  if (now - lastSampleTime >= sampleInterval) {
    lastSampleTime = now;

    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    flattenedMPU += String(a.acceleration.x, 3) + "," +
                    String(a.acceleration.y, 3) + "," +
                    String(a.acceleration.z, 3) + "," +
                    String(g.gyro.x, 3) + "," +
                    String(g.gyro.y, 3) + "," +
                    String(g.gyro.z, 3);

    sampleCount++;

    if (sampleCount < samplesPerBatch) {
      flattenedMPU += ",";
    }

    // Setelah 20 sampel (1 detik)
    if (sampleCount >= samplesPerBatch) {
      // Buat JSON payload
      DynamicJsonDocument doc(2048);
      GPSData hasil = getGPSData();
      JsonObject max30100 = doc.createNestedObject("max30100");
      max30100["heartrate"] = 93.3; // dummy
      max30100["spO2"] = 97;        // dummy

      doc["mpu6050"] = flattenedMPU;
      
      JsonObject gps = doc.createNestedObject("gt-u7");
      if (isnan(hasil.longitude)) {
        gps["longitude"] = 0;
      } else {
        gps["longitude"] = hasil.longitude;
      }

      if (isnan(hasil.latitude)) {
        gps["latitude"] = 0;
      } else {
        gps["latitude"] = hasil.latitude;
      }

      String jsonPayload;
      serializeJson(doc, jsonPayload);
      Serial.println("=== JSON Payload ===");
      Serial.println(jsonPayload);
      Serial.println("====================");

      sendData(jsonPayload);

      // Reset
      flattenedMPU = "";
      sampleCount = 0;
    }
  }
}