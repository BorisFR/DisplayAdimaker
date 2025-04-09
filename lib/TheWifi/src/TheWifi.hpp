#ifndef THE_WIFI_HPP
#define THE_WIFI_HPP

#include "../../../src/CONFIG.hpp"
#include <WiFiManager.h>

#define THE_WIFI_EVENT_CHANGE_IP std::function<void(String)>
#define THE_WIFI_EVENT std::function<void(WiFiEvent_t)>

class TheWifi
{
public:
    TheWifi();
    void setup();
    void loop();
    String getMacAddress();
    String getIP();
    void eventChangeIP(THE_WIFI_EVENT_CHANGE_IP callback);
    void donotuseevent(WiFiEvent_t event);
    void event(THE_WIFI_EVENT callback);

private:
    THE_WIFI_EVENT sendEvent;
    WiFiManager wm;
    String ipAddress = "x.x.x.x";
    bool ipIsValid = false;

    THE_WIFI_EVENT_CHANGE_IP theCallback;

    void connect();
};

#endif