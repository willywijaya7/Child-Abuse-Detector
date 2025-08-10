#include "Configuration.h"
#include <Arduino.h>

const char* SSID = "rayawifi";
const char* PASSWORD = "dotdotdotdot";
const char* SERVER_URL = "https://03a04e78c64d.ngrok-free.app";
const char* SERVER_POST = "https://03a04e78c64d.ngrok-free.app/datas/";
const int RXD_SIM = 16;
const int TXD_SIM = 17;
const int RXD_GPS = 34;
const int TXD_GPS = 35;
const int SDA_PIN = 21;
const int SCL_PIN = 22;