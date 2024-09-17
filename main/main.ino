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

TaskHandle_t Task1;
TaskHandle_t Task2;

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

    Serial.println(xPortGetFreeHeapSize());
    xTaskCreatePinnedToCore(
                    core0Task,   // Task function. /
                    "firebase operations",     / name of task. /
                    40000,       // Stack size of task /
                    NULL,        // parameter of the task /
                    1,           // priority of the task /
                    &Task1,      // Task handle to keep track of created task /
                    0);          // pin task to core 0 /    
    xTaskCreatePinnedToCore(
                    core1Task,   // Task function. /
                    "offline operations",     // name of task. /
                    10000,       // Stack size of task /
                    NULL,        // parameter of the task /
                    2,           // priority of the task /
                    &Task2,      // Task handle to keep track of created task /
                    1);          // pin task to core 1 
}

void core0Task( void * pvParameters ){
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());
  for(;;){
    handleFirebase(); // From FirebaseOperations.h
    getSolenoid(); // From FirebaseOperations.h
    //setVolume(); // From FirebaseOperations.h

  }
}

void core1Task( void * pvParameters ){
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    displayVolume(); // From LCDOperations.h
     yield();
  }
}
void loop()
{  
}

// cannot be put on module. let this stay here.... 
ICACHE_RAM_ATTR void increase()
{
    pulse++;
}