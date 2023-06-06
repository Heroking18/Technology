#include "Sensor.h"
#include <iostream>
#include <cstring>

using namespace std;

Sensor::~Sensor()
{
}

int Sensor::ReadLDR()
{
	int value = analogRead(SensorPin);

	if (value < 300)
	{
		return 1;//Car detected
	}
	else if (value > 300)
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
	if (Weight > 300)
	{
		return 1;//Car detected
	}
	else if (Weight < 300)
	{
		return 0; //No car detected
	}
	else
	{
		return -1; // error
	}
}
