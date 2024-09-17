#ifndef LCDOPERATIONS_H
#define LCDOPERATIONS_H

#include "globalVars.h"
#include "volume.h"


void initLCD() {
    lcd.init(); // lcd from globalVars.h
    lcd.clear();
    lcd.backlight();     // Make sure backlight is on
    lcd.setCursor(0, 0); // Set cursor to character 2 on line 0
    lcd.print("Starting");
}

void clearLCD() {
    lcd.clear();
}

void displayVolume() {
    float vol = volume(pulse); // pulse from globalVars.h
    lcd.setCursor(0, 1);
    lcd.print("Vol(L): ");
    lcd.setCursor(8, 1);
    lcd.print(vol);
}

void getOpLCD() {
    lcd.setCursor(0, 0);
    lcd.print("Get: ");
    lcd.setCursor(5, 0);
}

void setOpLCD() {
    lcd.setCursor(9, 0);
    lcd.print("Set: ");
    lcd.setCursor(14, 0);
}

#endif