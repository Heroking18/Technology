#include "ParkingCluster.h"
#include <iostream>

#include "Sensor.h"
#include "LED.h"
#include "Arduino.h"

using namespace std;

ParkingCluster::ParkingCluster(int LdrPin, int PressurePin, int RedLightPin, int GreenLightPin, int BlueLightPin)
 {
	//Default constructor
	/*---- Pins need to change ----*/
	Sensor clusterLdr = new Sensor(LdrPin);
	Sensor clusterPressure = new Sensor(PressurePin);
	LED clusterLED = new LED(RedLightPin, GreenLightPin, BlueLightPin);
}

ParkingCluster::~ParkingCluster()
{
	delete clusterLdr;
	delete clusterPressure;
	delete clusterLED;
}

int ParkingCluster::GetNumCarsParked() const
 {
	return NumCarsParked;
}
int ParkingCluster::GetAvailableParkingSpots() const
 {
	return AvailableParkingSpots;
}
int ParkingCluster::GetNumCarsEntered() const
 {
	return NumCarsEntered;
}
byte ParkingCluster::GetIP() const
 {
	return IP;
}
int ParkingCluster::GetTotalAvailableParkingSpots() const
 {
	return TotalAvailableParkingSpots;
}
void ParkingCluster::SetNumCarsParked(int CarsParked)
 {
	NumCarsParked = CarsParked;
	return
}
void ParkingCluster::SetNumCarsEntered(int CarsEntered)
 {
	NumCarsEntered = CarsEntered;
	return
}
void ParkingCluster::SetTotalAvailableParkingSpots(int AvailableSpots)
 {
	TotalAvailableParkingSPots = AvailableSpots; 
	return
}
int ParkingCluster::SetLedColour()
 {
	if (0)	// Connection has failed
	{
		LedElement.SetLedColour(255, 255, 0);	// Yellow
	}
	else if (AvailableParkingSpots == 0)	// Cluster full
	{
		LedElement.SetLedColour(255, 0, 0);	// Red
	}
	else if (AvailableParkingSpots != 0) // Cluster not full
	{
		LedElement.SetLedColour(0, 255, 0);	// Green
	}
	
	return 0;
}
int ParkingCluster::DetermineCarParked()
 {
	 //Check if the spot is occupied or not
	 if(clusterPressure.ReadPressure() == 1 && clusterLdr.ReadLDR() == 1 && !carParked)
	 {
		NumCarsParked++;
		AvailableParkingSpots--;
		TotalAvailableParkingSPots--;
		carParked = true;
		return 0;
	 }
	 else if((clusterPressure.ReadPressure() == 0 || clusterLdr.ReadLDR() == 0) && carParked)
	 {
		NumCarsParked--;
		AvailableParkingSpots++;
		TotalAvailableParkingSPots++;
		carParked = false;
	 }
	 else
	 {
		return -1;
	 }
}
