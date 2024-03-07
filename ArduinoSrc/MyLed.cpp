// Sets color mode if LED string

#include "MyLED.h"


  void MyLed::ledInit() {  //LCD initalization
    FastLED.addLeds< WS2812, LED_PIN, GRB>(leds, LED_NUM);
    FastLED.clear();
    FastLED.setBrightness(200);
    FastLED.show();
  }

  void MyLed::setMode(byte mode = 0) {  //LED modes
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

  void MyLed::ledOff() {  // turns off
    FastLED.clear();
    FastLED.show();
  }

  void MyLed::raindow() {  // default rainbow
    for (int i = 0; i < LED_NUM; i++) {
      leds[i].setHue(i * 255 / LED_NUM);
    }
    FastLED.show();
  }

  void MyLed::doubleCol(int a, int b) {  // 50% of LED color "a", 50% - "b"
    for (int i = 0; i < LED_NUM / 2; i++) {
      leds[i].setHue(a);
    }
    for (int i = LED_NUM / 2; i < LED_NUM; i++) {
      leds[i].setHue(b);
    }
    FastLED.show();
  }

  void MyLed::setBRT(int &BRT) {  // sets brightness
    FastLED.setBrightness(BRT);
    FastLED.show();
  }

  void MyLed::setColor(int col) {  // sets static color
    for (int i = 0; i < LED_NUM; i++) {
      leds[i].setHue(col);
    }
    FastLED.show();
  }

  void MyLed::setFlag() {
    statFlag = !statFlag;
  }
  
  bool MyLed::getFlag() {
    return statFlag;
  }
