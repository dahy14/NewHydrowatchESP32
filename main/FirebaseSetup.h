#ifndef FIREBASE_SETUP_H
#define FIREBASE_SETUP_H

#include <FirebaseClient.h>
#include "AsyncCallback.h"


#define API_KEY "AIzaSyBPp9CrojsQ4N7xrRRKE8Y_hc514ijjBgE"
#define DATABASE_URL "https://hy2c-f612d-default-rtdb.asia-southeast1.firebasedatabase.app"

DefaultNetwork network;
#define USER_EMAIL "ac@ac.com"
#define USER_PASSWORD "aaaaaa"

#if defined(ESP32) || defined(ESP8266) || defined(ARDUINO_RASPBERRY_PI_PICO_W)
#include <WiFiClientSecure.h>
WiFiClientSecure ssl_client;
#elif defined(ARDUINO_ARCH_SAMD) || defined(ARDUINO_UNOWIFIR4) || defined(ARDUINO_GIGA) || defined(ARDUINO_PORTENTA_C33) || defined(ARDUINO_NANO_RP2040_CONNECT)
#include <WiFiSSLClient.h>
WiFiSSLClient ssl_client;
#endif



using AsyncClient = AsyncClientClass;
AsyncClient aClient(ssl_client, getNetwork(network));

UserAuth user_auth(API_KEY, USER_EMAIL, USER_PASSWORD);
FirebaseApp app;

RealtimeDatabase Database;

void initFirebase()
{
    Serial.println("Initializing Firebase app...");

    ssl_client.setInsecure();

    initializeApp(aClient, app, getAuth(user_auth), asyncCB, "authTask");
    app.getApp<RealtimeDatabase>(Database);

    Database.url(DATABASE_URL);
    Serial.println("Firebase initialized.");
}

#endif // FIREBASE_SETUP_H
