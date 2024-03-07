#pragma once
#include <GParser.h>
#include "MyButton.h"
#include "MyL2C.h"
#include "MyLed.h"
#include "MyEncoder.h"

class MyParcer {

public:
  void myParcer(MyButton& btn, MyL2C& scr, MyLed& led, MyEncoder& myEnc); //working with inputs from PC
private:
};