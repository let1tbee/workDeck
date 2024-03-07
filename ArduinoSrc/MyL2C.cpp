//function recieves c-string and displays it on LCD screen

#include "MyL2C.h"

void MyL2C::screenFunc(char tmp[]) {  //Displays text on screen
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(tmp);
  _tmr = millis();
  flagTimer = 1;
}
void MyL2C::errorFunc(char tmp[]) {  //Displays error message on screen
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Error:");
  lcd.setCursor(1, 1);
  lcd.print(tmp);
  _tmr = millis();
  flagTimer = 1;
}

void MyL2C::initLCD() {  //Displays welcome screen
  if (flagInit) {
    lcd.init();
    lcd.backlight();
    flagInit = 0;
  }
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("workDeck:");
  lcd.setCursor(11, 1);
  lcd.print("Menu");
}

void MyL2C::backToMenu() {  //returns to welcome screen after "backDel" time
  if (flagTimer && millis() - _tmr >= backDel) {
    initLCD();
    flagTimer = 0;
  }
}
