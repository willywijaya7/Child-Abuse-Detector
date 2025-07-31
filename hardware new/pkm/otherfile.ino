#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>
//#include <MAX30100_PulseOximeter.h>
#define RXD_SIM 16  // SIM800L TX
#define TXD_SIM 17  // SIM800L RX

SoftwareSerial sim800(RXD_SIM, TXD_SIM);
// Sensor Objects
Adafruit_MPU6050 mpu;
//PulseOximeter pox;

// GPS Module
#define RXD_GPS 34
#define TXD_GPS 35
SoftwareSerial gpsSerial(RXD_GPS, TXD_GPS);

void setup() {
    Serial.begin(115200);
    Wire.begin();
    gpsSerial.begin(9600);
    sim800.begin(9600);

    delay(1000);
  Serial.println("Initializing SIM800L...");

  sim800.println("AT");
  delay(500);
  printResponse();

  sim800.println("AT+CMGF=1"); // Set SMS to text mode
  delay(500);
  printResponse();

  sim800.println("AT+CNMI=1,2,0,0,0"); // Configure to show SMS immediately
  delay(500);
  printResponse();

    // Initialize MPU6050
    if (!mpu.begin()) {
        Serial.println("Failed to initialize MPU6050");
        while (1);
    }
/**
    // Initialize MAX30100
    if (!pox.begin()) {
        Serial.println("Failed to initialize MAX30100");
        while (1);
    }
    pox.setOnBeatDetectedCallback(onBeatDetected);
}
**/
}
void loop() {
    // Read MPU6050
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    float accelMagnitude = sqrt(a.acceleration.x * a.acceleration.x + a.acceleration.y * a.acceleration.y + a.acceleration.z * a.acceleration.z);
    
    Serial.print("Acceleration Magnitude: ");
    Serial.println(accelMagnitude);
    
    // Detect abnormal motion
    if (accelMagnitude > 15) {
        Serial.println("WARNING: Strong shake detected!");
    }
    if (sim800.available()) {
    Serial.write(sim800.read());
  }
    /**
    // Read Heart Rate
    pox.update();
    float heartRate = pox.getHeartRate();
    Serial.print("Heart Rate: ");
    Serial.println(heartRate);
    
    if (heartRate > 160 || heartRate < 50) {
        Serial.println("WARNING: Abnormal heart rate detected!");
    }
    **/
    // Read and Debug GPS Data
    String gpsData = "";
    while (gpsSerial.available()) {
        char c = gpsSerial.read();
        gpsData += c;
    }
    
    if (gpsData.length() > 0) {
        Serial.println("Raw GPS Data:");
        Serial.println(gpsData);
        
        int rmcIndex = gpsData.indexOf("$GPRMC");
        int gsvIndex = gpsData.indexOf("$GPGSV");
        
        if (rmcIndex != -1) {
            String gprmc = gpsData.substring(rmcIndex, gpsData.indexOf("\n", rmcIndex));
            Serial.println("Parsed GPRMC Sentence:");
            Serial.println(gprmc);
            
            char *gpsArray = strdup(gprmc.c_str());
            char *token = strtok(gpsArray, ",");
            int field = 0;
            String status = "";
            String latRaw = "", latDir = "", lonRaw = "", lonDir = "";
            
            while (token != NULL) {
                field++;
                if (field == 3) status = token; // GPS status (A = valid, V = invalid)
                if (field == 4) latRaw = token;
                if (field == 5) latDir = token;
                if (field == 6) lonRaw = token;
                if (field == 7) lonDir = token;
                token = strtok(NULL, ",");
            }
            free(gpsArray);
            
            if (status == "A" && latRaw != "" && lonRaw != "") { // Only show if GPS data is valid
                float latitude = convertToDecimal(latRaw, latDir, true);
                float longitude = convertToDecimal(lonRaw, lonDir, false);
                Serial.print("Latitude: ");
                Serial.println(latitude, 6);
                Serial.print("Longitude: ");
                Serial.println(longitude, 6);
            } else {
                Serial.println("WARNING: GPS signal not fixed. Waiting for a valid fix...");
            }
        } else {
            Serial.println("WARNING: No valid $GPRMC sentence found. GPS data might be incomplete.");
        }
        
        // Extract number of satellites from GPGSV
        if (gsvIndex != -1) {
            String gpgsv = gpsData.substring(gsvIndex, gpsData.indexOf("\n", gsvIndex));
            Serial.println("Parsed GPGSV Sentence:");
            Serial.println(gpgsv);
            
            char *gsvArray = strdup(gpgsv.c_str());
            char *token = strtok(gsvArray, ",");
            int field = 0;
            int numSatellites = -1;
            
            while (token != NULL) {
                field++;
                if (field == 3) numSatellites = atoi(token);
                token = strtok(NULL, ",");
            }
            free(gsvArray);
            
            if (numSatellites != -1) {
                Serial.print("Number of Satellites: ");
                Serial.println(numSatellites);
            }
        }
    }
    
    delay(5000);
}
/**
void onBeatDetected() {
    Serial.println("Heart beat detected!");
}
**/
float convertToDecimal(String raw, String direction, bool isLatitude) {
    if (raw.length() < 4) return 0.0;
    
    int degreeDigits = isLatitude ? 2 : 3; // 2 digits for latitude, 3 for longitude
    float degrees = raw.substring(0, degreeDigits).toFloat();
    float minutes = raw.substring(degreeDigits).toFloat();
    float decimal = degrees + (minutes / 60.0);
    
    if (direction == "S" || direction == "W") {
        decimal *= -1;
    }
    return decimal;
}



void printResponse() {
  while (sim800.available()) {
    Serial.write(sim800.read());
  }
}