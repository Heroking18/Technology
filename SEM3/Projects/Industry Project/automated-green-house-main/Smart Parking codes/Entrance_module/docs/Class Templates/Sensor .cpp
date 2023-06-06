#include "Sensor.h"
#include <iostream>
#include <cstring>

using namespace std;

Sensor::Sensor()
 {
		//Default constructor
}

Sensor::~Sensor()
 {
	//Destructor
	delete this;
}

int Sensor::readLDR()
 {
	return 0;
}
int Sensor::readPreassure()
 {
	return 0;
}
