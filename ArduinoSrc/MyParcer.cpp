
#include "MyParcer.h"

  void MyParcer::myParcer(MyButton& btn, MyL2C& scr, MyLed& led, MyEncoder& myEnc) { //working with inputs from PC
    char str[50];
    int amount = Serial.readBytesUntil(';', str, 50);
    str[amount] = NULL;
    GParser data(str, ',');
    int ints[10];
    data.parseInts(ints);

    switch (ints[0]) {
      case 1://displays page on LCD
        btn.textDisp(scr, ints[1]); 
        break;
      case 2://Turn LED ON\OFF
        btn.ledStat(scr, led);
        break;
      case 3://Encoder input from PC
        if(led.getFlag()) {
          led.setMode(ints[1]);
          myEnc.setMode(ints[1]);
          myEnc.printMode(ints[1], scr, led);
        }
        else if (!led.getFlag()) scr.errorFunc("    LED is OFF");
        break;
      case 4://Slider input from PC sets brightness
        if(led.getFlag()) {
          led.setBRT(ints[1]);
          myEnc.setBRT(ints[1]);
          myEnc.printBRT(ints[1], scr, led);
        }
        else if (!led.getFlag()) scr.errorFunc("    LED is OFF");//If LED is OFF but input recieved sidplays Error message
        break;
    }
  }