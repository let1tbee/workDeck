//Button is checked with delay for being pressed and returns action

#pragma once
#include <Arduino.h>
#include "MyL2C.h"
#include "FastLED.h"
#include "MyLed.h"
#define btnDebug 500 // time of button Debug delay

class MyButton {

public:
  MyButton(byte btnPin);    //initiating, pinMode configuration
  bool btnAction();                      //Check click with timer, returns True on clic kor False
  void ledStat(MyL2C& scr, MyLed& led);  //Turns LED string off and on
  void openPage(MyL2C& scr, byte page); // sends identifier of buttons to PC
  void textDisp(MyL2C& scr,byte pageTMP); // displays name of triggered page
private:
  byte _btnPin;
  uint32_t _tmr;
  bool _flag;
  bool flagLED = 1;
};