#pragma once
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <Arduino.h>

class LED
{
private:
    int RedLightPin;
    int GreenLightPin;
    int BlueLightPin;
public:
    LED(int , int , int );
    ~LED();
    int SetLedColour(int, int, int);
};
