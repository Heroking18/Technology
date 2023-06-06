#pragma once

#include "Arduino.h"
#include "LiquidCrystal.h"

/*
Link for the library:
https://github.com/arduino-libraries/LiquidCrystal
*/

class LCD
{
private:
    int SCLPin;
    int SDAPin;
public:
    LCD(int, int) = default;
    ~LCD();

    int Display(String);
};
