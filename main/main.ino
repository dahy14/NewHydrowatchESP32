#include <Arduino.h>
#include <FirebaseClient.h>
#include "WifiSetup.h"
#include "FirebaseSetup.h"
#include "FirebaseOperations.h"
#include "globalVars.h"

void setup()
{
    pinMode(solenoidPin, OUTPUT); // solenoidPin From globalVars.h
    Serial.begin(115200);
    initWiFi(); // From WifiSetup.h
    initFirebase(); // From FirebaseSetup.h
}

void loop()
{
    handleFirebase(); // From FirebaseOperations.h
    getSolenoid(); // From FirebaseOperations.h 
}
