#ifndef __LCDH__
#define __LCDH__

#include "Arduino.h"
#include "LiquidCrystal.h"

/*
Link for the library:
https://github.com/arduino-libraries/LiquidCrystal
*/

class LCD
{

private:
    /* data */
public:
    LCD(/* args */);
    ~LCD();

    int display();
};

#endif