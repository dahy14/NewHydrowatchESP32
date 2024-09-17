#ifndef PINOUTS_H
#define PINOUTS_H 

#include <LiquidCrystal_I2C.h>

// extern makes them available to other files
// pinout
extern int solenoidPin = 26;
extern int flowSensorPin = 4;
extern int lcdSDAPin = 21;
extern int lcdSCLPin = 22; // 21 and 22 are the default pins for I2C, just declared it for clarity

// tenantIds and LCD 
extern int tenantId = 2;
extern LiquidCrystal_I2C lcd(0x27, 16, 2); // change depending on lcd

// global vars 
extern volatile long pulse = 0; 
extern bool online = true; 


void initPinmode() {
    pinMode(solenoidPin, OUTPUT); // solenoidPin From globalVars.h
    pinMode(flowSensorPin, INPUT);// flowSensorPin From globalVars.h
}


#endif 
