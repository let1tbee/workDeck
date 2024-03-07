//Encoder sends signal while being moved

#include "MyEncoder.h"

void MyEncoder::encAction(MyL2C& scr, MyLed& led) {
  _enc.tick();
  if (_enc.turn()) {
    if (_enc.right() && led.getFlag()) {  // by turning right changing mode positive
      rightBorder(mode, 1, modeNum);
      printMode(mode, scr, led);
    }
    if (_enc.left() && led.getFlag()) {  // by turning right changing mode negative
      leftBorder(mode, 1, modeNum);
      printMode(mode, scr, led);
    }
    if (_enc.rightH() && led.getFlag()) {  // changing brightness from 0 - 255 by turning right with press
      rightBorder(ledBRT, 10, 250);
      printBRT(ledBRT, scr, led);
    }
    if (_enc.leftH() && led.getFlag()) {  // changing brightness from 0 - 255 by turning left with press
      leftBorder(ledBRT, 10, 250);
      printBRT(ledBRT, scr, led);
    } else if (!led.getFlag()) scr.errorFunc("    LED is OFF");
  }
}

void MyEncoder::printMode(int temp, MyL2C& scr, MyLed& led) {  //display and remembers Mode on LCD
  itoa(temp, textMode + 6, DEC);
  scr.screenFunc(textMode);
  led.setMode(temp);
  Serial.print("3,");
  Serial.print(temp);
}

void MyEncoder::printBRT(int temp, MyL2C& scr, MyLed& led) {  //displays and remembers brightness on LCD
  itoa(temp, textBRT + 11, DEC);
  scr.screenFunc(textBRT);
  led.setBRT(temp);
  Serial.print("4,");
  Serial.print(temp);
}

void MyEncoder::leftBorder(int& var, int numChange, int borderNum) {  //checking left side border and redirects to the end of the list
  if (var >= 0) var -= numChange;
  if (var < 0) var = borderNum;
}

void MyEncoder::rightBorder(int& var, int numChange, int borderNum) {  //checking right side border and redirects to the start of the list
  if (var <= borderNum) var += numChange;
  if (var > borderNum) var = 0;
}

void MyEncoder::setMode(int tmp) {
  mode = tmp;
}

void MyEncoder::setBRT(int tmp) {
  ledBRT = tmp;
}
