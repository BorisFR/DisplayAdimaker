#ifndef THE_NTP_HPP
#define THE_NTP_HPP

#include "../../../src/CONFIG.hpp"
#include "WiFi.h"
#include <WiFiUdp.h>
#include <ezTime.h>

class TheNTP
{
public:
    TheNTP();
    void setup();
    void loop();
    bool isOk();
    String currentDateTime(String format);
    uint8_t second();
    uint8_t minute();
    uint8_t hour();

private:
    WiFiUDP ntpUDP;
    Timezone timeZone;
    bool ntpOk;
};

#endif