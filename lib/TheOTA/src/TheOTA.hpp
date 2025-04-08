#ifndef THE_OTA_HPP
#define THE_OTA_HPP

#include "../../../src/CONFIG.hpp"
#include "WiFi.h"
#include <ArduinoOTA.h> // from espressif ESP32 package, not the "official" arduino

class TheOTA
{
public:
    TheOTA();
    void setup();
    void loop();

private:
};

#endif