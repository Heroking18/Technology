#include "ParkingCluster.h"
#include "LED.h"
#include "Sensor.h"
#include <iostream>
#include <cstring>

using namespace std;

ParkingCluster::ParkingCluster()
 {
		//Default constructor
}

ParkingCluster::~ParkingCluster()
 {
	//Destructor
	delete this;
}

int ParkingCluster::getNumCarsParked()
 {
	return 0;
}
int ParkingCluster::getAvailableParkingSpots()
 {
	return 0;
}
int ParkingCluster::getNumCarsEntered()
 {
	return 0;
}
int ParkingCluster::getIP()
 {
	return 0;
}
int ParkingCluster::getTotalAvailableParkingSpots()
 {
	return
}
void ParkingCluster::setNumCarsParked(int carsParked)
 {
	return
}
void ParkingCluster::setNumCarsEntered(int carsEntered)
 {
	return
}
void ParkingCluster::setTotalAvailableParkingSpots(int availableSpots)
 {
	return
}
int ParkingCluster::toggleLed()
 {
	return 0;
}
int ParkingCluster::determineCarParked()
 {
	return 0;
}
