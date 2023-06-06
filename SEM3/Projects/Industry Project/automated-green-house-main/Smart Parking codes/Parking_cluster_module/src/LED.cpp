/**
 * @file LED.cpp
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
#include "LED.h"

using namespace std;

LED::LED(int RedPin, int GreenPin, int BluePin)
: RedLightPin(RedPin)
, GreenLightPin(GreenPin)
, BlueLightPin(BluePin)
{
}

LED::~LED()
{
}

int LED::SetLedColour(int RedLightValue, int GreenLightValue, int BlueLightValue)
{
	if (RedLightValue < 0 || RedLightValue > 255 || GreenLightValue < 0 || 
	GreenLightValue > 255 || BlueLightValue < 0 || 	BlueLightValue > 255)
	{
		return -1;
	}
	analogWrite(RedLightPin, RedLightValue);
 	analogWrite(GreenLightPin, GreenLightValue);
  	analogWrite(BlueLightPin, BlueLightValue);

	return 0;
}
