#pragma once
#include <GParser.h>

class MyParcer {

public:
  void myParcer(MyButton& btn, MyL2C& scr, MyLed& led, MyEncoder& myEnc) {
    char str[50];
    int amount = Serial.readBytesUntil(';', str, 50);
    str[amount] = NULL;
    GParser data(str, ',');
    int ints[10];
    data.parseInts(ints);

    switch (ints[0]) {
      case 2:
        btn.ledStat(scr, led);
        break;
      case 3:
        if(led.getFlag()) {
          led.setMode(ints[1]);
          myEnc.setMode(ints[1]);
          myEnc.printMode(ints[1], scr, led);
        }
        else if (!led.getFlag()) scr.errorFunc("    LED is OFF");
        break;
      case 4:
        if(led.getFlag()) {
          led.setBRT(ints[1]);
          myEnc.setBRT(ints[1]);
          myEnc.printBRT(ints[1], scr, led);
        }
        else if (!led.getFlag()) scr.errorFunc("    LED is OFF");
        break;
    }
  }

private:
};