#pragma once
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <Arduino.h>

class Sensor 
{
private:
    int SensorPin;
public:
    Sensor(int);
    ~Sensor();
    int ReadLDR();
    int ReadPressure();
};
