#include <Arduino.h>
#include <FirebaseClient.h>
#include <time.h>
#include <sntp.h>

#include "WifiSetup.h"
#include "FirebaseSetup.h"
#include "FirebaseOperations.h"
#include "globalVars.h"
#include "NTPtime.h"

// For configuring Time
const char *ntpServer1 = "pool.ntp.org";
const char *ntpServer2 = "time.nist.gov";
const long gmtOffset_sec = 25200;
const int daylightOffset_sec = 3600;
// const char* time_zone = "CET-1CEST,M3.5.0,M10.5.0/3";  // TimeZone rule for Europe/Rome including daylight adjustment rules (optional)
void setup()
{
    pinMode(solenoidPin, OUTPUT); // solenoidPin From globalVars.h
    pinMode(flowSensorPin, INPUT);// flowSensorPin From globalVars.h
    attachInterrupt(digitalPinToInterrupt(flowSensorPin), increase, RISING);

    Serial.begin(115200);
    initWiFi(); // From WifiSetup.h
    initFirebase(); // From FirebaseSetup.h

    sntp_set_time_sync_notification_cb(timeavailable);
    sntp_servermode_dhcp(1);
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
}

void loop()
{
    handleFirebase(); // From FirebaseOperations.h
    // getSolenoid(); // From FirebaseOperations.h
    setVolume(pulse); // From FirebaseOperations.h
}


ICACHE_RAM_ATTR void increase()
{
    pulse++;
}