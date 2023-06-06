#include "LCD.h"
#include <iostream>
#include <Wire.h>


using namespace std;

LCD::LCD(int sclPin, int sdaPin)
{
    SCLPin = sclPin;
    SDAPin = sdaPin;
}

LCD::~LCD()
{
    
}

int LCD::Display(String msg)
{   
    LiquidCrystal(SCL, SDA);

    lcd.begin(16, 2);
    lcd.print("testing"); // to be changed to actual values
    return 0;
}
