#include "LED.h"
#include <iostream>
#include <cstring>

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
	if (RedLightValue == NULL || RedLightValue > 255 || GreenLightValue == NULL || 
	GreenLightValue > 255 || BlueLightValue == NULL || 	BlueLightValue > 255)
	{
		return -1;
	}
	analogWrite(RedLightPin, RedLightValue);
 	analogWrite(GreenLightPin, GreenLightValue);
  	analogWrite(BlueLightPin, BlueLightValue);

	return 0;
}
