#pragma once
#include <cstddef>

class LED
{
private:
    int RedLightPin;
    int GreenLightPin;
    int BlueLightPin;
public:
    LED(int, int, int) = default;
    ~LED();
    int ChangeLED(int, int, int);
};
