
#include "CONFIG.hpp"
#include <Arduino.h>

bool dataChanged = false;
unsigned long memoSendsLastTime;
String uid = "";

/* ***************************************************************************
  Json
*************************************************************************** */
#include <ArduinoJson.h>
JsonDocument jsonData;

/* ***************************************************************************
  Settings
*************************************************************************** */
#include "TheSettings.hpp"
TheSettings theSettings;

#ifdef USE_WIFI
/* ***************************************************************************
  WiFi
*************************************************************************** */
#include "TheWifi.hpp"
TheWifi theWifi;
void theWifiChangeIP(String value)
{
  jsonData["ip"] = value;
}
#endif

#ifdef USE_OTA
/* ***************************************************************************
  OTA
*************************************************************************** */
#include "TheOTA.hpp"
TheOTA theOTA;
#endif

#ifdef USE_NTP
/* ***************************************************************************
  NTP
*************************************************************************** */
#include "TheNTP.hpp"
TheNTP theNTP;
#endif

#ifdef USE_MQTT
/* ***************************************************************************
  MQTT
*************************************************************************** */
#pragma region
#include "TheMQTT.hpp"
TheMQTT theMQTT;

void receivedData(char *topic, byte *payload, unsigned int length)
{
  JsonDocument document;
  deserializeJson(document, payload, length);
  String jsonString;
  serializeJson(document, jsonString);
  Serial.println("Received JSON: " + jsonString);
}

void publishData(String topic, JsonDocument data)
{
  data["timestamp"] = dateTime("YmdHis");
  data["rssi"] = -WiFi.RSSI();
  String message;
  serializeJson(data, message);
  theMQTT.publish(topic, message);
}

void mqttConnected()
{
  jsonData["version"] = IOT_VERSION;
  jsonData["platform"] = IOT_PLATFORM;
  jsonData["ota_password"] = OTA_PASSWORD;
  publishData("device", jsonData);
  jsonData.remove("ota_password");
  jsonData.remove("version");
  jsonData.remove("platform");
  jsonData.remove("attach");
}
#pragma endregion
#endif

#ifdef USE_FIREBASE
/* ***************************************************************************
  Database
*************************************************************************** */
#pragma region
#include "TheDB.hpp"
TheDB theDB;
byte dbTryCount = 0;

void dbGetInfos()
{
  if (theMQTT.isValid())
    return;
  if (!theDB.ready())
    return;
  if (theDB.dataAvailable())
  {
    Serial.println("Getting data");
    delay(1000);
    String result = theDB.getData();
    JsonDocument document;
    deserializeJson(document, result);
    const char *ip = document["IP"];
    String mqttIpAddress = String(ip);
    const char *user = document["User"];
    String mqttUser = String(user);
    const char *password = document["Password"];
    String mqttPassword = String(password);
    Serial.println("Database get MQTT IP: " + mqttIpAddress);
    theMQTT.doInit(uid, mqttIpAddress, mqttUser, mqttPassword);
    theSettings.settingsSaveOneString("mqttip", mqttIpAddress);
    theSettings.settingsSaveOneString("mqttuser", mqttUser);
    theSettings.settingsSaveOneString("mqttpass", mqttPassword);
    return;
  }
  if (!theDB.requestInProgress())
  {
    dbTryCount++;
    if (dbTryCount < 2)
    {
      Serial.println("Launch request");
      delay(1000);
      theDB.requestData("/MQTT1");
    }
    else
    {
      Serial.println("/!\\ Too much database try");
      String ip = theSettings.getString("", DEFAULT_MQTT_SERVER);
      String user = theSettings.getString("", DEFAULT_MQTT_USER);
      String password = theSettings.getString("", DEFAULT_MQTT_PASSWORD);
      // TODO: get infos from preferences
      theMQTT.doInit(uid, ip, user, password);
    }
    return;
  }
}
#pragma endregion
#endif

#include "TheScreen.hpp"
TheScreen theScreen;

uint16_t myWhite, myBlack, myBlue;
String textDateTime = "";
uint8_t decalColor = 0;

void setup()
{
  Serial.begin(115200);
  delay(1500);
  Serial.println("** I.o.T.");
  Serial.println("Version: " + String(IOT_VERSION));
  Serial.println("Platform: " + String(IOT_PLATFORM));
  theSettings.setup();
  theScreen.setup();
  myWhite = theScreen.colorRGB(255, 255, 255);
  myBlack = theScreen.colorRGB(0, 0, 0);
  myBlue = theScreen.colorRGB(0, 0, 255);
#ifdef USE_WIFI
  theWifi.eventChangeIP(theWifiChangeIP);
  uid = "ESP32-" + theWifi.getMacAddress();
  Serial.println("UID: " + uid);
  jsonData["id"] = uid;
  delay(500);
#endif
#ifdef USE_WIFI
  theWifi.setup();
#endif
#ifdef USE_OTA
  theOTA.setup();
#endif
  delay(500);
#ifdef USE_NTP
  theNTP.setup();
#endif
#ifdef USE_FIREBASE
  theDB.setup();
#endif
  uint32_t addon = 0;
  jsonData["attach"] = addon;
#ifdef USE_MQTT
  theMQTT.eventConnected(mqttConnected);
  theMQTT.eventReceive(receivedData);
  theMQTT.setup();
#endif
}

uint8_t previousSecond, previousMinute, previousHour;

void loop()
{
#ifdef USE_WIFI
  theWifi.loop();
#endif
#ifdef USE_OTA
  theOTA.loop();
#endif
#ifdef USE_NTP
  theNTP.loop();
#endif
#ifdef USE_FIREBASE
  theDB.loop();
  dbGetInfos();
#endif
#ifdef USE_MQTT
  theMQTT.loop();
#endif
#ifdef USE_MQTT
  if (millis() - memoSendsLastTime >= HEARTBEAT_DELAY)
    dataChanged = true;
  if (dataChanged)
  {
    publishData("sensors", jsonData);
    memoSendsLastTime = millis();
  }
  dataChanged = false;
#endif
  theScreen.externalRainbowRectangle(decalColor++);
  if (previousSecond != theNTP.second())
  {
    previousSecond = theNTP.second();
    String temp = theNTP.currentDateTime("s");
    theScreen.drawFillRectangle(14 + 6 * 12, 9, 2 * 12, 14, myBlack);
    theScreen.printText(temp.c_str(), 2, 14 + 6 * 12, false, myWhite, 255);
    if (previousMinute != theNTP.minute())
    {
      previousMinute = theNTP.minute();
      temp = theNTP.currentDateTime("i");
      theScreen.drawFillRectangle(14 + 3 * 12, 9, 2 * 12, 14, myBlack);
      theScreen.printText(temp.c_str(), 2, 14 + 3 * 12, false, myWhite, 255);

      if (previousHour != theNTP.hour())
      {
        previousHour = theNTP.hour();
        temp = theNTP.currentDateTime("H:i:s d/m/Y");
        // theScreen.clear();
        // 1 caractère taille 2 => w 12 x h 14
        theScreen.drawFillRectangle(14, 9, 19 * 12, 14, myBlack);
        theScreen.printText(temp.c_str(), 2, 14, false, myWhite, 255);
      }
    }
  }
  theScreen.loop();
}
