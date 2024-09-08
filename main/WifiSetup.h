#ifndef WIFI_SETUP_H
#define WIFI_SETUP_H

#include <WiFi.h>
#include <WiFiMulti.h>

// #define WIFI_SSID "Naypes Residence"
// #define WIFI_PASSWORD "BWCTnaPLDT1234!"

WiFiMulti wifiMulti;

#define WIFI_SSID "Naypes Residence TPLink"
#define WIFI_PASSWORD "Pass123!"


void initWiFi()
{
  Serial.print("Connecting to Wi-Fi");

   // Add list of wifi networks wifMulliti ==10 seconds bootup. 
  wifiMulti.addAP("Naypes Residence", "BWCTnaPLDT1234!");
  wifiMulti.addAP("naypes Residence TPLink", "Pass123!");
  wifiMulti.addAP("Hg", "zxcvbnmz");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
      Serial.println("no networks found");
  } 
  else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
      delay(5);
    }
  }

  // Connect to Wi-Fi using wifiMulti (connects to the SSID with strongest connection)
  Serial.println("Connecting Wifi...");
  if(wifiMulti.run() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }

    // faster but inflexible,  only one way to connect...
    // WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    // while (WiFi.status() != WL_CONNECTED)
    // {
    //     Serial.print(".");
    //     delay(300);
    // }

}

#endif // WIFI_SETUP_H
