#ifndef CONFIG_HPP
#define CONFIG_HPP

/* ***************************************************************************
  Global Configuration
*************************************************************************** */

#define USE_WIFI
#ifdef USE_WIFI
#define USE_NTP
// #define USE_OTA
// #define USE_MQTT
#ifdef USE_MQTT
#define USE_FIREBASE
#endif
#endif

#define HEARTBEAT_DELAY 60 * 1000
// Program
#define IOT_VERSION 1.5
#define COPY_LINE1 " \xA9 2025 by JUNIA"
#define COPY_LINE2 "** St. Fardoux **"
// WiFi
#define PORTAL_NAME "I.o.T."
// For Other The Air update firmware
// Network Time Protocol
#define NTP_SERVER_EU "europe.pool.ntp.org"
#define NTP_REFRESH 3 * 60 * 60 // 3 hours
#define NTP_SYNC_TIMEOUT 60
// Firebase
#include "SECRET.hpp"

#endif