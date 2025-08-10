
#ifndef JSON_BUILDER_H
#define JSON_BUILDER_H

#include <Arduino.h>
#include "MAX30100Handler.h"

String buildJSON(const String &mpuData, const HeartRateData &hr);

#endif
