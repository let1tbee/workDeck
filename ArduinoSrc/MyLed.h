// Sets color mode if LED string

#pragma once
#include "FastLED.h"

#define LED_PIN 9    // pin data LED
#define LED_NUM 120  // number of leds in LED String

class MyLed {

public:
  void ledInit();  //LCD initalization

  void setMode(byte mode = 0);  //LED modes

  void ledOff();  // turns off

  void raindow();  // default rainbow

  void doubleCol(int a, int b);  // 50% of LED color "a", 50% - "b"

  void setBRT(int &BRT);  // sets brightness

  void setColor(int col);  // sets static color

  void setFlag();
  
  bool getFlag();
  
private:
  CRGB leds[LED_NUM];
  bool statFlag = 0;
};