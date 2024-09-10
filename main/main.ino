#include <Arduino.h>
#include <FirebaseClient.h>

#include "globalVars.h"
#include "WifiSetup.h"
#include "FirebaseSetup.h"
#include "NTPtime.h"
#include "FirebaseOperations.h"


void setup()
{
    pinMode(solenoidPin, OUTPUT); // solenoidPin From globalVars.h
    pinMode(flowSensorPin, INPUT);// flowSensorPin From globalVars.h
    attachInterrupt(digitalPinToInterrupt(flowSensorPin), increase, RISING);

    Serial.begin(115200);
    initWiFi(); // From WifiSetup.h
    initFirebase(); // From FirebaseSetup.h
    initNTP(); // From NTPtime.h
}

void loop()
{
    handleFirebase(); // From FirebaseOperations.h
    getSolenoid(); // From FirebaseOperations.h
    setVolume(); // From FirebaseOperations.h
}


ICACHE_RAM_ATTR void increase()
{
    pulse++;
}