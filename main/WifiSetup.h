#ifndef WIFI_SETUP_H
#define WIFI_SETUP_H

#include <WiFi.h>

#define WIFI_SSID "Naypes Residence"
#define WIFI_PASSWORD "BWCTnaPLDT1234!"

void initWiFi()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();
}

#endif // WIFI_SETUP_H
