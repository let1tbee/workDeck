// Sets color mode if LED string

#pragma once
#include "FastLED.h"

#define LED_PIN 9    // pin data LED
#define LED_NUM 120  // number of leds in LED String

class MyLed {

public:
  void ledInit() {  //LCD initalization
    FastLED.addLeds< WS2812, LED_PIN, GRB>(leds, LED_NUM);
    FastLED.clear();
    FastLED.setBrightness(200);
    FastLED.show();
  }

  void setMode(byte mode = 0) {  //LED modes
    switch (mode) {
      case 0:
        raindow();
        break;
      case 1:
        setColor(50);
        break;
      case 2:
        setColor(90);
        break;
      case 3:
        setColor(120);
        break;
      case 4:
        setColor(180);
        break;
      case 5:
        setColor(240);
        break;
      case 6:
        setColor(0);
        break;
      case 7:
        doubleCol(0, 50);
        break;
      case 8:
        doubleCol(90, 120);
        break;
      case 9:
        doubleCol(180, 240);
        break;
      case 10:
        doubleCol(50, 180);
        break;
    }
  }

  void ledOff() {  // turns off
    FastLED.clear();
    FastLED.show();
  }
  void raindow() {  // default rainbow
    for (int i = 0; i < LED_NUM; i++) {
      leds[i].setHue(i * 255 / LED_NUM);
    }
    FastLED.show();
  }
  void doubleCol(int a, int b) {  // 50% of LED color "a", 50% - "b"
    for (int i = 0; i < LED_NUM / 2; i++) {
      leds[i].setHue(a);
    }
    for (int i = LED_NUM / 2; i < LED_NUM; i++) {
      leds[i].setHue(b);
    }
    FastLED.show();
  }

  void setBRT(int &BRT) {  // sets brightness
    FastLED.setBrightness(BRT);
    FastLED.show();
  }
  void setColor(int col) {  // sets static color
    for (int i = 0; i < LED_NUM; i++) {
      leds[i].setHue(col);
    }
    FastLED.show();
  }
  void setFlag() {
    statFlag = !statFlag;
  }
  bool getFlag() {
    return statFlag;
  }
private:
  CRGB leds[LED_NUM];
  bool statFlag = 0;
};