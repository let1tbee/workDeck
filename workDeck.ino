#pragma once
#include <Arduino.h>
#include "ArduinoSrc/MyButton.h"
#include "ArduinoSrc/MyButton.cpp"
#include "ArduinoSrc/MyEncoder.h"
#include "ArduinoSrc/MyEncoder.cpp"
#include "ArduinoSrc/MyL2C.h"
#include "ArduinoSrc/MyL2C.cpp"
#include "ArduinoSrc/MyLed.h"
#include "ArduinoSrc/MyLed.cpp"
#include "ArduinoSrc/MyParcer.h"
#include "ArduinoSrc/MyParcer.cpp"

//Button pins
#define btn1 2
#define btn2 3
#define btn3 4
#define btn4 5

MyButton action1(btn1);
MyButton action2(btn2);
MyButton action3(btn3);
MyButton action4(btn4);
MyEncoder myEnc;
MyL2C scr;
MyLed led;
MyParcer parc;

// Protocol for communication Arduino with PC
//1, 1-3; buttons redirects to pages
//2, 0-1; LED state status
//3, 0-1; 0 - turn left, 1 - turn right
//4, 0-1; 0 - turn left with press, 41 - turn right with press

//Protocol for communication PC with Arduino
//2, 0-1; LED state status
//3, 0-10; mode
//4, 0-250; brightness

void setup() {
  Serial.begin(115200);
  scr.initLCD();
  led.ledInit();
}

void loop() {
  myEnc.encAction(scr, led); //waiting for input from encoder
  if (Serial.available()) parc.myParcer(action4, scr, led, myEnc); // Parcing inputs from PC
  if (action1.btnAction()) action1.openPage(scr,1);//waiting for input from buttons
  if (action2.btnAction()) action2.openPage(scr,2);
  if (action3.btnAction()) action3.openPage(scr,3);
  if (action4.btnAction()) action4.ledStat(scr, led);
  scr.backToMenu(); // function returns to welcome screen within some delay
}
