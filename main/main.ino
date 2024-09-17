#include <Arduino.h>
#include <FirebaseClient.h>
#include <LiquidCrystal_I2C.h>
#include "WifiSetup.h"
#include "FirebaseSetup.h"
#include "NTPtime.h"
#include "FirebaseOperations.h"
#include "LCDOperations.h"
#include "globalVars.h"
#include "volume.h"

void setup()
{
    initLCD();// From LCDOperations.h
    Serial.begin(115200);
    initPinmode(); // From globalVars.h
    attachInterrupt(digitalPinToInterrupt(flowSensorPin), increase, RISING); // flowSensorPin From globalVars.h 
    initWiFi(); // From WifiSetup.h
    initNTP(); // From NTPtime.h
    initFirebase(); // From FirebaseSetup.h
    clearLCD(); // From LCDOperations.h
}

void loop()
{
    displayVolume(); // From LCDOperations.h
    handleFirebase(); // From FirebaseOperations.h
    getSolenoid(); // From FirebaseOperations.h
    setVolume(); // From FirebaseOperations.h
}

// cannot be put on module. let this stay here.... 
ICACHE_RAM_ATTR void increase()
{
    pulse++;
}


