#include "TheWifi.hpp"

TheWifi *theWifiInstance;

static void WiFiEvent(WiFiEvent_t event)
{
    theWifiInstance->donotuseevent(event);
}

TheWifi::TheWifi() { theWifiInstance = this; }

void TheWifi::event(THE_WIFI_EVENT callback)
{
    sendEvent = callback;
    Serial.println("TheWiFi callback set");
}

void TheWifi::donotuseevent(WiFiEvent_t event)
{
    switch (event)
    {
    case SYSTEM_EVENT_STA_START: // 2
        Serial.println("** WiFi (2): try to connect");
        break;
    case SYSTEM_EVENT_STA_STOP: // 3
        Serial.println("** WiFi (3): stop trying");
        break;
    case SYSTEM_EVENT_STA_CONNECTED: // 4
        Serial.println("** WiFi (4): STA connect");
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED: // 5
        Serial.println("** WiFi (5): trying");
        break;
    case SYSTEM_EVENT_STA_GOT_IP: // 7
        Serial.println("** WiFi (7): got ip");
        break;
    case SYSTEM_EVENT_STA_LOST_IP: // 8
        Serial.println("** WiFi (8): lost ip");
        break;
    case SYSTEM_EVENT_STA_BSS_RSSI_LOW: // 9
        Serial.println("** WiFi (9): low rssi");
        break;
    case SYSTEM_EVENT_STA_WPS_ER_SUCCESS: // 10
        Serial.println("** WiFi (10): error");
        break;
    case SYSTEM_EVENT_STA_WPS_ER_FAILED: // 11
        Serial.println("** WiFi (11): STA WPS failed");
        break;
    case SYSTEM_EVENT_AP_START: // 15
        Serial.println("** WiFi (15): AP start");
        break;
    default:
        Serial.println("** WiFi:" + String(event));
        break;
    }
    if (sendEvent)
        sendEvent(event);
}

void TheWifi::setup()
{
    WiFi.mode(WIFI_STA);
    // reset settings - wipe credentials for testing
    // Serial.println("WiFi: reset settings");
    // wm.resetSettings();
    wm.setConfigPortalBlocking(true);
    wm.setConfigPortalTimeout(120);
    wm.setConnectTimeout(20);
    WiFi.onEvent(WiFiEvent);
    // WiFi.onEvent(WiFiStartAP, SYSTEM_EVENT_AP_START);
    connect();
}

void TheWifi::loop()
{
    wm.process();
    if (WiFi.status() != WL_CONNECTED)
    {
        WiFi.reconnect();
        // connect();
    }
}

void TheWifi::connect()
{
    // automatically connect using saved credentials if they exist
    // If connection fails it starts an access point with the specified name
    bool wifiOk = false;
    uint8_t count = 2;
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