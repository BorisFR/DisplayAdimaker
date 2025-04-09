
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
#include <PNGdec.h>
PNG png;
#include "logo_junia.hpp"
// 1 caractère taille 2 => w 12 x h 14
#define CHAR_SIZE2_WIDTH 12
#define CHAR_SIZE2_HEIGHT 14

uint8_t bright = 128;
uint16_t myWhite, myBlack, myBlue;
String textDateTime = "";
uint8_t decalRainbowColor = 0;

bool isPngReady = false;
uint16_t pngX = 0;
uint16_t pngY = 0;

typedef struct my_private_struct
{
  int xoff, yoff; // corner offset
} PRIVATE;
void PNGDraw(PNGDRAW *pDraw)
{
  uint16_t usPixels[320];
  uint8_t ucMask[40];
  PRIVATE *pPriv = (PRIVATE *)pDraw->pUser;
  png.getLineAsRGB565(pDraw, usPixels, PNG_RGB565_BIG_ENDIAN, 0xffffffff);
  for (uint16_t x = 0; x < pDraw->iWidth; x++)
  {
    theScreen.drawPixel(pngX + x, pngY + pDraw->y, usPixels[x]);
  }
  if ((png.getHeight() - 1) == pDraw->y)
  {
    isPngReady = true;
  }
} // PNGDraw()

void displayPNG(int x, int y, const char *data, uint16_t length)
{
  isPngReady = false;
  pngX = x;
  pngY = y;
  int rc = png.openRAM((uint8_t *)data, length, PNGDraw);
  if (rc == PNG_SUCCESS)
  {
    PRIVATE priv;
    Serial.printf("image specs: %d x %d, %d bpp, pixel type: %d\n", png.getWidth(), png.getHeight(), png.getBpp(), png.getPixelType());
    while (!isPngReady)
    {
      priv.xoff = rand() & 0xff;
      priv.yoff = rand() % 160;
      rc = png.decode((void *)&priv, 0);
    }
    png.close();
  }
  return;
}

void displayLogo(uint16_t x = 0)
{
  // uint16_t x = 0; // (PANEL_SIZE_WIDTH - 66) / 2;
  displayPNG(x, 0, logo_junia_66_32_map, logo_junia_66_32_SIZE);
}

uint8_t stateWifi = 0;
// 1 : STA connecting
// 2 : STA OK
// 3 : AP
// 4 : STA error so next is portal

String textToDisplay = "";

void displayState()
{
  theScreen.clear();
  theScreen.printText(textToDisplay.c_str(), 2, 0, true, myWhite, myBlack, bright);
}

void wifiCallback(WiFiEvent_t code)
{
  switch (code)
  {
  case SYSTEM_EVENT_STA_START: // 2
    stateWifi = 1;
    textToDisplay = "WiFi: Connecting";
    displayState();
    break;
  case SYSTEM_EVENT_STA_STOP: // 3
    if (stateWifi == 1)
    {
      stateWifi = 4;
      textToDisplay = "WiFi: STOP";
    }
    else
    {
      stateWifi = 0;
      textToDisplay = "WiFi: STOP";
    }
    displayState();
    break;
  case SYSTEM_EVENT_STA_CONNECTED: // 4
    stateWifi = 2;
    textToDisplay = "WiFi: OK";
    displayState();
    break;
  case SYSTEM_EVENT_STA_DISCONNECTED: // 5
    if (stateWifi == 1)
    {
      textToDisplay = textToDisplay + ".";
      displayState();
    }
    break;
  case SYSTEM_EVENT_STA_GOT_IP: // 7
    break;
  case SYSTEM_EVENT_STA_LOST_IP: // 8
    break;
  case SYSTEM_EVENT_STA_WPS_ER_SUCCESS: // 10
    break;
  case SYSTEM_EVENT_STA_WPS_ER_FAILED: // 11
    if (stateWifi == 4)
    {
      textToDisplay = String(PORTAL_NAME);
      displayState();
      displayLogo();
    }
    break;
  case SYSTEM_EVENT_AP_START: // 15
    stateWifi = 3;
    textToDisplay = ">" + String(PORTAL_NAME);
    displayState();
    displayLogo();
    break;
  default:
    Serial.println("** WiFi: " + String(code));
    break;
  }
}

uint8_t previousSecond, previousMinute, previousHour = 99;
#define DATE_TIME_TEXT_SIZE 2
#define DATE_TIME_CHAR_NUMBERS 6 + 2 + 1 + 8 + 2
// (  64 * 4 = 256  - (19 * 12) = 228   ) = 28 / 2
// #define DATE_TIME_X (PANEL_SIZE_WIDTH - (DATE_TIME_CHAR_NUMBERS * CHAR_SIZE2_WIDTH)) / 2
#define DATE_TIME_X 14
#define DATE_TIME_Y (PANEL_SIZE_HEIGHT - CHAR_SIZE2_HEIGHT) / 2

#define DATE_TIME_BORDER 3

void displayDateTime()
{
  theScreen.externalRainbowRectangle(decalRainbowColor++, DATE_TIME_BORDER);
#ifdef USE_NTP
  // if (!theNTP.isOk())
  //   return;
  //  change hour?
  if (previousHour != theNTP.hour())
  {
    String temp = theNTP.currentDateTime("H:i:s d/m/Y");
    // theScreen.clear();
    // theScreen.drawFillRectangle(DATE_TIME_X, DATE_TIME_Y, DATE_TIME_CHAR_NUMBERS * CHAR_SIZE2_WIDTH, CHAR_SIZE2_HEIGHT, 0, 0, 0);
    // theScreen.printText(temp.c_str(), DATE_TIME_TEXT_SIZE, DATE_TIME_X, false, myWhite, bright);
    theScreen.printText(temp.c_str(), DATE_TIME_TEXT_SIZE, DATE_TIME_X, false, myWhite, myBlack, bright);
    previousHour = theNTP.hour();
    previousMinute = theNTP.minute();
    previousSecond = theNTP.second();
  }
  else
  {
    // change second?
    if (previousSecond != theNTP.second())
    {
      String temp = theNTP.currentDateTime("s");
      // theScreen.drawFillRectangle(DATE_TIME_X + 6 * CHAR_SIZE2_WIDTH, DATE_TIME_Y, 2 * CHAR_SIZE2_WIDTH, CHAR_SIZE2_HEIGHT, 0, 0, 0);
      // theScreen.printText(temp.c_str(), DATE_TIME_TEXT_SIZE, DATE_TIME_X + 6 * CHAR_SIZE2_WIDTH, false, myWhite, bright);
      theScreen.printText(temp.c_str(), DATE_TIME_TEXT_SIZE, DATE_TIME_X + 6 * CHAR_SIZE2_WIDTH, false, myWhite, myBlack, bright);
      previousSecond = theNTP.second();
      // change minute?
      if (previousMinute != theNTP.minute())
      {
        temp = theNTP.currentDateTime("i");
        // theScreen.drawFillRectangle(DATE_TIME_X + 3 * CHAR_SIZE2_WIDTH, DATE_TIME_Y, 2 * CHAR_SIZE2_WIDTH, CHAR_SIZE2_HEIGHT, 0, 0, 0);
        // theScreen.printText(temp.c_str(), DATE_TIME_TEXT_SIZE, DATE_TIME_X + 3 * CHAR_SIZE2_WIDTH, false, myWhite, bright);
        theScreen.printText(temp.c_str(), DATE_TIME_TEXT_SIZE, DATE_TIME_X + 3 * CHAR_SIZE2_WIDTH, false, myWhite, myBlack, bright);
        previousMinute = theNTP.minute();
      }
    }
  }
#endif
}

void setup()
{
  Serial.begin(115200);
  delay(1500);
  Serial.println("** I.o.T.");
  Serial.println("Version: " + String(IOT_VERSION));
  Serial.println("Platform: " + String(IOT_PLATFORM));
  theSettings.setup();
  theScreen.setup();
  displayLogo();
  delay(1000);
  myWhite = theScreen.colorRGB(255, 255, 255);
  myBlack = theScreen.colorRGB(0, 0, 0);
  myBlue = theScreen.colorRGB(0, 0, 255);
#ifdef USE_WIFI
  theWifi.event(wifiCallback);
  theWifi.eventChangeIP(theWifiChangeIP);
  uid = "ESP32-" + theWifi.getMacAddress();
  Serial.println("UID: " + uid);
  jsonData["id"] = uid;
  delay(500);
#endif
#ifdef USE_WIFI
  theWifi.setup();
#endif
  theScreen.clear();
  theScreen.printText("Connect :)", 2, 0, true, myWhite, myBlack, bright);
#ifdef USE_OTA
  theOTA.setup();
#endif
  delay(500);
  theScreen.clear();
  theScreen.printText("Getting date & time", 2, 0, true, myWhite, myBlack, bright);
#ifdef USE_NTP
  theNTP.setup();
  theScreen.clear();
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
  displayLogo();
  delay(1000);
  theScreen.clear();
}

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
  displayDateTime();
  //  displayLogo();

  theScreen.loop();
}
