#ifndef HTTPHELPER_H
#define HTTPHELPER_H
#include <Arduino.h>

bool kirimPesanKeServer(const char* serverURL, const String& pesan);

#endif
