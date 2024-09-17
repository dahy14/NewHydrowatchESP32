#ifndef LCDOPERATIONS_H
#define LCDOPERATIONS_H
#include <LiquidCrystal_I2C.h>
#include "volume.h"

if (tenantId == 1) {
    LiquidCrystal_I2C lcd(0x3F, 16, 2);
} else if (tenantId == 2){ 
    LiquidCrystal_I2C lcd(0x27, 16, 2);
} else {}

void initLCD() {
    lcd.init();
    lcd.clear();
    lcd.backlight();     // Make sure backlight is on
    lcd.setCursor(0, 0); // Set cursor to character 2 on line 0
    lcd.print("Starting");
}

void clearLCD() {
    lcd.clear();
}

void displayVolume() {
    float vol = volume(pulse);
    lcd.setCursor(0, 1);
    lcd.print("Vol(L): ");
    lcd.setCursor(8, 1);
    lcd.print(vol);
}

#endif