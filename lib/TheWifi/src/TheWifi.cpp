#include "TheWifi.hpp"

TheWifi::TheWifi() {}

void TheWifi::setup()
{
    WiFi.mode(WIFI_STA);
    // reset settings - wipe credentials for testing
    // Serial.println("WiFi: reset settings");
    // wm.resetSettings();
    wm.setConfigPortalBlocking(true);
    wm.setConfigPortalTimeout(120);
    wm.setConnectTimeout(20);
    connect();
}

void TheWifi::loop()
{
    wm.process();
    if (WiFi.status() != WL_CONNECTED)
    {
        connect();
    }
}

void TheWifi::connect()
{
    // automatically connect using saved credentials if they exist
    // If connection fails it starts an access point with the specified name
    bool wifiOk = false;
    uint8_t count = 3;
    Serial.print("WiFi: try to connect");
    while (!wifiOk && count > 0)
    {
        if (wm.autoConnect(PORTAL_NAME))
        {
            Serial.println();
            Serial.println("WiFi: connected");
            wifiOk = true;
            ipAddress = WiFi.localIP().toString();
            ipIsValid = true;
            Serial.println("IP is " + ipAddress);
            if (theCallback)
            {
                Serial.println("Wifi: callback done");
                theCallback(ipAddress);
            }
            else
            {
                Serial.println("Wifi: no callback");
            }
        }
        else
        {
            Serial.print(".");
            delay(2000); // 2 seconds
            count--;
        }
    }
    Serial.println();
    // Serial.println("End connectWifi()");
}

String TheWifi::getMacAddress()
{
    String temp = WiFi.macAddress();
    temp.replace(":", "");
    return temp;
}

String TheWifi::getIP()
{
    return ipAddress;
}

void TheWifi::eventChangeIP(THE_WIFI_EVENT_CHANGE_IP callback)
{
    theCallback = callback;
    Serial.println("WiFi callback set");
}