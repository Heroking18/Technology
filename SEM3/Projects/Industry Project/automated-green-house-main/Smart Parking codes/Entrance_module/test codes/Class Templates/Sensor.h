#pragma once
#include <cstddef>

class Sensor
{
private:
    int SensorPin;
public:
    Sensor(int Pin){SensorPin = Pin};
    ~Sensor();
    int ReadLDR();
    int ReadPressure();
};
