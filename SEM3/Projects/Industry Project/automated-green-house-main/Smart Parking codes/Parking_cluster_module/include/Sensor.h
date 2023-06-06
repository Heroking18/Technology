/**
 * @file Sensor.h
 * @authors
 * Daniel García López (4976215​)
 * Andre Sanao (4425553)
 * @brief 
 * @version 0.1
 * @date 2023-01-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
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
