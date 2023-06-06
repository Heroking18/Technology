#include "LCD.h"
#include <iostream>

using namespace std;

LCD::LCD(int scl, int sda) : SCL(scl), SDA(sda), lcd(0x27, 16, 2)
{
}

LCD::~LCD()
{
}

int LCD::Display()
{
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("message");
    return 0;
}
