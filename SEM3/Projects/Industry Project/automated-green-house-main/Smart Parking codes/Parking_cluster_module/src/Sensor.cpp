/**
 * @file Sensor.cpp
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
#include "Sensor.h"

using namespace std;

Sensor::Sensor(int pin)
{
	SensorPin = pin;
}

Sensor::~Sensor()
{
}

int Sensor::ReadLDR()
{
	int value = analogRead(SensorPin);

	if (value < 3000)
	{
		return 1;//Car detected
	}
	else if (value > 3000)
	{
		return 0; //No car detected
	}
	else
	{
		return -1; // error
	}
}
int Sensor::ReadPressure()
{
	int Weight = analogRead(SensorPin);
	if (Weight > 4000)
	{
		return 1;//Car detected
	}
	else if (Weight <= 4000)
	{
		return 0; //No car detected
	}
	else
	{
		return -1; // error
	}
}
