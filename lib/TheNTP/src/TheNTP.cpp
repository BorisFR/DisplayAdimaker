#include "TheNTP.hpp"

TheNTP::TheNTP() {}

void TheNTP::setup()
{
    ntpOk = false;
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.print("/!\\ NTP: Mise à l'heure de l'esp32 impossible, aucune connexion réseau");
        return;
    }
    Serial.print("NTP: Mise à l'heure de l'esp32 en cours");
    setDebug(INFO);
    setServer(NTP_SERVER_EU);
    setInterval(NTP_REFRESH);
    waitForSync(NTP_SYNC_TIMEOUT);
    timeZone.setLocation("Europe/Paris");
    Serial.println("UTC:" + UTC.dateTime());
    Serial.println("Local time: " + timeZone.dateTime());
    ntpOk = true;
    // Serial.println("monformat: " + dateTime("YmdHis"));
}

void TheNTP::loop()
{
    if (!ntpOk)
    {
        setup();
        if (!ntpOk)
            return;
    }
    events();
}

String TheNTP::currentDateTime(String format)
{
    return timeZone.dateTime(format);
}

uint8_t TheNTP::second() { return timeZone.second(); }
uint8_t TheNTP::minute() { return timeZone.minute(); }
uint8_t TheNTP::hour() { return timeZone.hour(); }
