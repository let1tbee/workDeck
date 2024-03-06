//function recieves c-string and displays it on LCD screen

#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#define backDel 5000  //delay of going to welcome screen

class MyL2C {
public:

  void screenFunc(char tmp[]) {  //Displays text on screen
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print(tmp);
    _tmr = millis();
    flagTimer = 1;
  }
  void errorFunc(char tmp[]) {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Error:");
    lcd.setCursor(1, 1);
    lcd.print(tmp);
    _tmr = millis();
    flagTimer = 1;
  }

  void initLCD() {  //Displays welcome screen
    if (flagInit) {
      lcd.init();
      lcd.backlight();
      flagInit = 0;
    }
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("workDeck:");
    lcd.setCursor(11, 1);
    lcd.print("Menu");
  }
  void backToMenu() {  //returns to welcome screen after "backDel" time
    if (flagTimer && millis() - _tmr >= backDel) {
      initLCD();
      flagTimer = 0;
    }
  }


private:
  LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
  uint32_t _tmr;
  bool flagInit = 1;
  bool flagTimer = 0;
};