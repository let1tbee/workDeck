#include "HardwareSerial.h"
#include "MyButton.h"

MyButton::MyButton(byte btnPin) {
  _btnPin = btnPin;
  pinMode(_btnPin, INPUT_PULLUP);
}
bool MyButton::btnAction() {
  bool btnState = digitalRead(_btnPin);
  if (!btnState && !_flag && millis() - _tmr >= btnDebug) {  // flag up on first loop and after releasing the button
    _flag = true;
    _tmr = millis();
  }
  if (btnState && _flag && millis() - _tmr >= btnDebug) {
    _flag = false;
    _tmr = millis();
    return true;  // true if pressed
  }
  return false;  // false if unpressed
}
void MyButton::ledStat(MyL2C& scr, MyLed& led) { // Turns on and off led string
  switch (flagLED) {
    case (1):
      scr.screenFunc("Led String ON");
      Serial.print("2,1");
      led.setFlag();
      led.setMode(0);
      break;
    case (0):
      scr.screenFunc("Led String OFF");
      Serial.print("2,0");
      led.setFlag();
      led.ledOff();
      break;
  }
  flagLED = !flagLED;
}
