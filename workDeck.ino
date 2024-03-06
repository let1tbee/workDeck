#pragma once
#include <Arduino.h>
#include "MyButton.h"
#include "MyEncoder.h"
#include "MyL2C.h"
#include "MyLed.h"
#include "MyParcer.h"

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
  myEnc.encAction(scr, led);
  if (Serial.available()) parc.myParcer(action4,scr,led,myEnc); //make a function!
  if (action1.btnAction()) scr.screenFunc("Youtube");
  if (action2.btnAction()) scr.screenFunc("Wikipedia");
  if (action3.btnAction()) scr.screenFunc("Arduino");
  if (action4.btnAction()) action4.ledStat(scr, led);
  scr.backToMenu();
  
}
