#ifndef NTP_Time_H
#define NTP_Time_H
#include "time.h"
#include "sntp.h"


const char *ntpServer = "pool.ntp.org";

// Timer variables (send new readings every three minutes)
unsigned long sendDataPrevMillis = 0;
unsigned long timerDelay = 5000;



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

#endif