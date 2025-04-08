#include "TheSettings.hpp"

TheSettings::TheSettings()
{
}

void TheSettings::setup()
{
    Serial.println("** Settings read");
    theSettings.begin(SETTINGS, RO_MODE);
    if (theSettings.isKey(SETTINGS_IS_INIT) == false)
    {
        settingsIsOk = false;
        Serial.println("No settings detect");
        return;
    }
}

void TheSettings::reset()
{
    theSettings.end();
    Serial.println("** Deleting all settings");
    theSettings.begin(SETTINGS, RW_MODE);
    theSettings.clear();
    theSettings.end();
    theSettings.begin(SETTINGS, RO_MODE);
    settingsIsOk = false;
}

unsigned long TheSettings::settingsUL(String key, unsigned long defaultValue)
{
    unsigned long value = theSettings.getULong64(key.c_str(), defaultValue);
    return theSettings.getULong64(key.c_str(), defaultValue);
}

String TheSettings::getString(String key, String defaultValue)
{
    return theSettings.getString(key.c_str(), defaultValue);
}

void TheSettings::settingsSaveOneUL(String key, unsigned long value)
{
    theSettings.end();
    Serial.println("** Writing settings");
    theSettings.begin(SETTINGS, RW_MODE);
    Serial.println("Save: " + key + " => " + String(value));
    theSettings.putULong64(key.c_str(), value);
    theSettings.end();
    theSettings.begin(SETTINGS, RO_MODE);
}

void TheSettings::settingsSaveOneString(String key, String value)
{
    theSettings.end();
    Serial.println("** Writing settings");
    theSettings.begin(SETTINGS, RW_MODE);
    Serial.println("Save: " + key + " => " + value);
    theSettings.putString(key.c_str(), value);
    theSettings.end();
    theSettings.begin(SETTINGS, RO_MODE);
}