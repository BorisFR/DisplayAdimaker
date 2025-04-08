#ifndef THE_SETTINGS_HPP
#define THE_SETTINGS_HPP

#include <Preferences.h>

#define SETTINGS "settings"
#define RW_MODE false
#define RO_MODE true
#define SETTINGS_IS_INIT "isInit"
#define SETTINGS_KEY_SERVERIP "srvip"
#define SETTINGS_KEY_MQTTUSR "mqusr"
#define SETTINGS_KEY_MQTTPWD "mqpwd"
#define SETTINGS_NO_VALUE "*"

class TheSettings
{
public:
    TheSettings();
    void setup();
    void reset();
    unsigned long settingsUL(String key, unsigned long defaultValue);
    void settingsSaveOneUL(String key, unsigned long value);
    void settingsSaveOneString(String key, String value);
    String getString(String key, String defaultValue);

private:
    // to store settings in ESP32's memory
    Preferences theSettings;
    // to know if settings are ok or not
    bool settingsIsOk = false;
};

#endif