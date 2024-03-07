//Encoder sends signal while being moved

#pragma once
#include <Arduino.h>
#include <EncButton.h>
#include "MyL2C.h"
#include "MyLed.h"
#include "FastLED.h"
#define LED_BRT 200  //default LED brightness
#define modeNum 10   //cap of modes

class MyEncoder {

public:
  void encAction(MyL2C& scr, MyLed& led);

  void printMode(int temp, MyL2C& scr, MyLed& led);  //display and remembers Mode on LCD

  void printBRT(int temp, MyL2C& scr, MyLed& led);  //displays and remembers brightness on LCD

  void leftBorder(int& var, int numChange, int borderNum);  //checking left side border and redirects to the end of the list

  void rightBorder(int& var, int numChange, int borderNum);  //checking right side border and redirects to the start of the list

  void setMode(int tmp);

  void setBRT(int tmp);

private:
  EncButton _enc = EncButton(7, 8, 6);
  int mode = 0;
  int ledBRT = LED_BRT;
  char textMode[10] = "Mode #0   ";
  char textBRT[15] = "Brightness     ";
};