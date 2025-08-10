#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <MAX30100_PulseOximeter.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>

// ===== PENGATURAN WIFI =====
const char* ssid = "Poco X3 Pro";
const char* password = "lalalalala";
const char* serverURL = "https://63946df92d68.ngrok-free.app/datas/"; // Pastikan URL ini benar

// ===== PENGATURAN GPS (GT-U7) =====
#define GPS_RX_PIN 34 // Hubungkan ke pin TX modul GPS
#define GPS_TX_PIN 35 // Hubungkan ke pin RX modul GPS
TinyGPSPlus gps;
HardwareSerial gpsSerial(2); // Gunakan Hardware Serial port 2

// ===== OBJEK SENSOR =====
Adafruit_MPU6050 mpu;
PulseOximeter pox;

// ===== PENGATURAN UNTUK MULTI-CORE =====
TaskHandle_t networkTaskHandle;
volatile bool dataReadyForSending = false;

// ===== PENGATURAN WAKTU =====
unsigned long lastSampleTime = 0;
const int sampleInterval = 20; // 20ms -> 50Hz

// ===== BUFFER DATA =====
DynamicJsonDocument jsonDoc(4096);
String flattenedMPUData = "";
int sampleCount = 0;
const int samplesPerBatch = 50; // (50Hz * 1 detik) = 50 sampel

// ===== VARIABEL DATA =====
// 'volatile' penting untuk variabel yang diakses dari dua core berbeda
volatile float lastHeartRate = 0;
volatile float lastSpO2 = 0;
volatile double lastLatitude = -1.0;
volatile double lastLongitude = -1.0;
bool max30100Available = false;

// ===== FUNGSI CALLBACK UNTUK DETEKSI DETAK JANTUNG =====
void onBeatDetected() {
  // Serial.println("♥");
}

// =================================================================
// ===== TUGAS JARINGAN (BERJALAN DI CORE 0) =====
// =================================================================
void networkTask(void *pvParameters) {
  Serial.println("Network task started on Core 0.");
  for (;;) {
    if (dataReadyForSending) {
      String payloadToSend;
      noInterrupts();
      serializeJson(jsonDoc, payloadToSend);
      dataReadyForSending = false;
      interrupts();

      if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\n=== Mengirim Payload ===");
        Serial.println(payloadToSend);
        Serial.println("========================");

        HTTPClient http;
        http.begin(serverURL);
        http.addHeader("Content-Type", "application/json");

        int httpResponseCode = http.POST(payloadToSend);

        if (httpResponseCode > 0) {
          Serial.print("HTTP Response code: ");
          Serial.println(httpResponseCode);
          String response = http.getString();
          if (response.length() > 150) {
             Serial.println(response.substring(0, 150) + "...");
          } else {
             Serial.println(response);
          }
        } else {
          Serial.print("Gagal mengirim data. Error code: ");
          Serial.println(httpResponseCode);
        }
        http.end();
      } else {
        Serial.println("WiFi tidak terhubung, pengiriman data dibatalkan.");
      }
    }
    vTaskDelay(10);
  }
}

// =================================================================
// ===== SETUP (BERJALAN DI CORE 1) =====
// =================================================================
void setup() {
  Serial.begin(115200);
  
  Wire.begin(21, 22, 400000);

  // --- KONEKSI WIFI ---
  Serial.println("Menghubungkan ke WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Tersambung.");
  Serial.print("Alamat IP: ");
  Serial.println(WiFi.localIP());

  // --- INISIALISASI MPU6050 ---
  if (!mpu.begin()) {
    Serial.println("Inisialisasi MPU6050 GAGAL! Periksa koneksi.");
    while (true);
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("MPU6050 siap.");

  // --- INISIALISASI MAX30100 ---
  Serial.println("Inisialisasi MAX30100...");
  delay(1000);
  if (!pox.begin()) {
    Serial.println("Inisialisasi MAX30100 GAGAL! Periksa kabel dan daya.");
    max30100Available = false;
  } else {
    Serial.println("MAX30100 siap.");
    max30100Available = true;
    pox.setOnBeatDetectedCallback(onBeatDetected);
    pox.setIRLedCurrent(MAX30100_LED_CURR_11MA); 
    Serial.println("Letakkan jari Anda pada sensor...");
  }

  // --- INISIALISASI GT-U7 (GPS) ---
  Serial.println("Inisialisasi GT-U7 GPS...");
  gpsSerial.begin(9600, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
  Serial.println("GT-U7 siap. Menunggu sinyal GPS...");

  // --- MEMBUAT TUGAS JARINGAN ---
  xTaskCreatePinnedToCore(
      networkTask, "NetworkTask", 10000, NULL, 1, &networkTaskHandle, 0);

  Serial.println("Setup selesai. Memulai koleksi data di Core 1...");
}

// =================================================================
// ===== LOOP UTAMA (BERJALAN DI CORE 1) =====
// =================================================================
void loop() {
  // --- PROSES DATA GPS (NON-BLOCKING) ---
  // Terus baca data dari modul GPS jika ada
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      // Setiap kali sebuah kalimat NMEA berhasil di-parse,
      // perbarui data lokasi jika valid.
      if (gps.location.isValid()) {
        lastLatitude = gps.location.lat();
        lastLongitude = gps.location.lng();
      }
    }
  }
  
  // --- PEMBACAAN MAX30100 ---
  if (max30100Available) {
    pox.update();
    float newHeartRate = pox.getHeartRate();
    float newSpO2 = pox.getSpO2();
    if (newHeartRate > 20 && newHeartRate < 220) lastHeartRate = newHeartRate;
    if (newSpO2 > 50 && newSpO2 <= 100) lastSpO2 = newSpO2;
  }

  // --- PENGAMBILAN SAMPEL MPU6050 ---
  if (millis() - lastSampleTime >= sampleInterval) {
    lastSampleTime = millis();
    
    if (!dataReadyForSending) {
      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);

      flattenedMPUData += String(a.acceleration.x, 3) + "," +
                        String(a.acceleration.y, 3) + "," +
                        String(a.acceleration.z, 3) + "," +
                        String(g.gyro.x, 3) + "," +
                        String(g.gyro.y, 3) + "," +
                        String(g.gyro.z, 3);
      
      sampleCount++;

      if (sampleCount < samplesPerBatch) {
        flattenedMPUData += ",";
      }
      
      if (sampleCount >= samplesPerBatch) {
        jsonDoc.clear();

        JsonObject heart = jsonDoc.createNestedObject("max30100");
        if (max30100Available) {
          heart["heartrate"] = lastHeartRate;
          heart["spO2"] = lastSpO2;
          heart["status"] = "connected";
        } else {
          heart["heartrate"] = -1;
          heart["spO2"] = -1;
          heart["status"] = "disconnected";
        }
        
        JsonObject gpsJson = jsonDoc.createNestedObject("gt-u7");
        gpsJson["latitude"] = lastLatitude;
        gpsJson["longitude"] = lastLongitude;

        jsonDoc["mpu6050"] = flattenedMPUData;

        dataReadyForSending = true;

        Serial.printf("HR: %.2f BPM, SpO2: %.2f %%, Lat: %f, Lng: %f\n", lastHeartRate, lastSpO2, lastLatitude, lastLongitude);

        flattenedMPUData = "";
        sampleCount = 0;
      }
    }
  }
}
