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
	if (Weight > 2800)
	{
		return 1;//Car detected
	}
	else if (Weight <= 2800)
	{
		return 0; //No car detected
	}
	else
	{
		return -1; // error
	}
}
