//function recieves c-string and displays it on LCD screen

#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#define backDel 5000  //delay of going to welcome screen

class MyL2C {
public:

  void screenFunc(char tmp[]);  //Displays text on screen

  void errorFunc(char tmp[]);  //Displays error message on screen

  void initLCD();  //Displays welcome screen

  void backToMenu();  //returns to welcome screen after "backDel" time

private:
  LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
  uint32_t _tmr;
  bool flagInit = 1;
  bool flagTimer = 0;
};