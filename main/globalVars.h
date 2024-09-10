#ifndef PINOUTS_H
#define PINOUTS_H

// extern makes them available to other files
// pinout
extern int solenoidPin = 26;
extern int flowSensorPin = 4;
extern int lcdSDAPin = 21;
extern int lcdSCLPin = 22;

// tenantIds 
extern int tenantId = 2;

// global vars 
extern volatile long pulse = 0; 
#endif 
