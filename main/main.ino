#include <Arduino.h>
#include <FirebaseClient.h>

#include "WifiSetup.h"
#include "FirebaseSetup.h"
#include "FirebaseOperations.h"




void setup()
{
    Serial.begin(115200);
    // Initialize Wi-Fi
    initWiFi();
    // Initialize Firebase
    initFirebase();

}

void loop()
{
    // Handle Firebase tasks
    handleFirebase();

    // Start Firebase operations like GET or SET
    startFirebaseOperations();
}
