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
