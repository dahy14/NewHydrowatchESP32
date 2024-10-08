#ifndef FIREBASE_SETUP_H
#define FIREBASE_SETUP_H

#include <FirebaseClient.h>
#include "AsyncCallback.h"

//com state led by naypes
// #define API_KEY "AIzaSyCWZ0VcS-8Cjh0exCpIUuzx9czdUJPLefA"
// #define DATABASE_URL "https://coms-stateled-default-rtdb.asia-southeast1.firebasedatabase.app"
// hydrowatch 
#define API_KEY "AIzaSyAk7BXj1SDqUeLHW9BbYbnHZKI5Li02U9E"
#define DATABASE_URL "https://hydrowatch-39591-default-rtdb.asia-southeast1.firebasedatabase.app"

DefaultNetwork network;
// esp client email for com state led 
// #define USER_EMAIL "ac@ac.com"
// #define USER_PASSWORD "aaaaaa"
// esp client email for hydrowatch
#define USER_EMAIL "client@esp.com"
#define USER_PASSWORD "123456"


#if defined(ESP32) || defined(ESP8266) || defined(ARDUINO_RASPBERRY_PI_PICO_W)
#include <WiFiClientSecure.h>
WiFiClientSecure ssl_client;
#elif defined(ARDUINO_ARCH_SAMD) || defined(ARDUINO_UNOWIFIR4) || defined(ARDUINO_GIGA) || defined(ARDUINO_PORTENTA_C33) || defined(ARDUINO_NANO_RP2040_CONNECT)
#include <WiFiSSLClient.h>
WiFiSSLClient ssl_client;
#endif



using AsyncClient = AsyncClientClass;
extern AsyncClient aClient(ssl_client, getNetwork(network));

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
