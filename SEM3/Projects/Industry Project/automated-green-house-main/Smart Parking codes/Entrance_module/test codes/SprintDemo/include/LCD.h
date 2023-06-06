#pragma once

#include "Arduino.h"
#include <LiquidCrystal_I2C.h>


class LCD
{
private:
    int SCL;
    int SDA;
    LiquidCrystal_I2C lcd;

public:
    LCD(int, int);
    ~LCD();

    int Display();
};
