#ifndef NTP_Time_H
#define NTP_Time_H
#include "time.h"
#include "sntp.h"


const char *ntpServer = "pool.ntp.org";

// For configuring Time
const char *ntpServer1 = "time.google.com";
const char *ntpServer2 = "pool.ntp.org";
const long gmtOffset_sec = 25200;
const int daylightOffset_sec = 3600;
// const char* time_zone = "CET-1CEST,M3.5.0,M10.5.0/3";  // TimeZone rule for Europe/Rome including daylight adjustment rules (optional)

String getTime()
{
    int now[3];
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return ("Not yet obtained");
    }
    now[0] = timeinfo.tm_hour;
    now[1] = timeinfo.tm_min;
    now[2] = timeinfo.tm_sec;

    if ((timeinfo.tm_mon + 1) < 10)
    {
        return String(timeinfo.tm_year + 1900) + "-0" + String(timeinfo.tm_mon + 1) + "-" + String(timeinfo.tm_mday) + " " +
               String(now[0]) + ":" + String(now[1]) + ":" + String(now[2]);
    }
    else
    {
        return String(timeinfo.tm_year + 1900) + "-" + String(timeinfo.tm_mon + 1) + "-" + String(timeinfo.tm_mday) + " " +
               String(now[0]) + ":" + String(now[1]) + ":" + String(now[2]);
    }
}

// Callback function (get's called when time adjusts via NTP)
void timeavailable(struct timeval *t)
{
    Serial.println("Got time adjustment from NTP!");
    getTime();
}


void initNTP() {
    sntp_set_time_sync_notification_cb(timeavailable);
    sntp_servermode_dhcp(1);
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
}
#endif