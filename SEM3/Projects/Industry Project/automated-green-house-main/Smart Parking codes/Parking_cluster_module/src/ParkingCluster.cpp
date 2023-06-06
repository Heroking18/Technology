/**
 * @file ParkingCluster.cpp
 * @authors
 * Mitchell van ‘t Kruys (4058151​)
 * Daniel García López (4976215​)
 * Nick Mulders (4523504​)
 * @brief 
 * @version 0.1
 * @date 2023-01-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "ParkingCluster.h"
#include <iostream>

#define BROKECLUSTERBUTTON 13
using namespace std;


/**
 * @brief Construct a new Parking Cluster:: Parking Cluster object
 * 
 * @param LdrPin 
 * @param PressurePin 
 * @param RedLightPin 
 * @param GreenLightPin 
 * @param BlueLightPin 
 * @param YellowButtonPin 
 * @param RedButtonPin 
 * @param BlueButtonPin 
 * @param BlackButtonPin 
 */
ParkingCluster::ParkingCluster(int LdrPin, int PressurePin, int RedLightPin, int GreenLightPin, int BlueLightPin,
int YellowButtonPin, int RedButtonPin, int BlueButtonPin, int BlackButtonPin)
	: TotalAvailableParkingSpotsInCluster(0),
	AvailableParkingSpots(5),
	NumCarsParked(0),
	NumCarsEntered(0)
{
	clusterLdr = new Sensor(LdrPin);
	clusterPressure = new Sensor(PressurePin);
	clusterLED = new LED(RedLightPin, GreenLightPin, BlueLightPin);
	YellowButton = new Button(YellowButtonPin);
	RedButton = new Button(RedButtonPin);
	BlueButton = new Button(BlueButtonPin);
	BlackButton = new Button(BlackButtonPin);

	SetNumCarsParked(0);
	SetNumCarsEntered(0); // Delete when entrance module is finished
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
int ParkingCluster::GetAvailableParkingSpotsInCluster() const
{
	return AvailableParkingSpots;
}
int ParkingCluster::GetNumCarsEntered() const
{
	return NumCarsEntered;
}
uint16_t ParkingCluster::GetIP() const
{
	return IP;
}
int ParkingCluster::GetTotalAvailableParkingSpotsInGarage() const
{
	return TotalAvailableParkingSpotsInCluster;
}
void ParkingCluster::SetNumCarsParked(int CarsParked)
{
	NumCarsParked = CarsParked;
}
void ParkingCluster::SetNumCarsEntered(int CarsEntered)
{
	NumCarsEntered = CarsEntered;
}
void ParkingCluster::SetTotalAvailableParkingSpotsInCluster(int AvailableSpots)
{
	TotalAvailableParkingSpotsInCluster = AvailableSpots; 
}
int ParkingCluster::ChangeLedColour()
{
	if (0)	// Connection has failed
	{
		clusterLED->SetLedColour(255, 255, 0);	// Yellow
	}
	else if (AvailableParkingSpots == 0)
	{
		clusterLED->SetLedColour(255, 0, 0);	// Red
	}
	else
	{
		clusterLED->SetLedColour(0, 255, 0);	// Green
	}
	
	return 0;
}

void ParkingCluster::HandleCarParked(bool *boolean)
{
	NumCarsParked++;
	AvailableParkingSpots--;
	TotalAvailableParkingSpotsInCluster--;
	*boolean = true;
}

void ParkingCluster::HandleCarLeft(bool *boolean)
{
	NumCarsParked--;
	AvailableParkingSpots++;
	TotalAvailableParkingSpotsInCluster++;
	*boolean = false;
}

int ParkingCluster::DetermineCarParked()
{
	//Check if the spot is occupied or not
	//Serial.println(YellowButton->Debounce());
	if((clusterPressure->ReadPressure() == 1 && clusterLdr->ReadLDR() == 1) && !carSensorParked)
	{
		HandleCarParked(&carSensorParked);
	}
	else if((clusterPressure->ReadPressure() == 0 && clusterLdr->ReadLDR() == 0) && carSensorParked)
	{
		HandleCarLeft(&carSensorParked);
	}
	else if ((YellowButton->Pressed()) && !carYellowParked)
	{
		HandleCarParked(&carYellowParked);
	}
	else if ((!YellowButton->Pressed()) && carYellowParked)
	{
		HandleCarLeft(&carYellowParked);	
	}
	else if ((RedButton->Pressed()) && !carRedParked)
	{
		HandleCarParked(&carRedParked);	
	}
	else if ((!RedButton->Pressed()) && carRedParked)
	{
		HandleCarLeft(&carRedParked);	
	}
	else if ((BlueButton->Pressed()) && !carBlueParked)
	{
		HandleCarParked(&carBlueParked);	
	}
	else if ((!BlueButton->Pressed()) && carBlueParked)
	{
		HandleCarLeft(&carBlueParked);	
	}
	else if ((BlackButton->Pressed()) && !carBlackParked)
	{
		HandleCarParked(&carBlackParked);
	}
	else if ((!BlackButton->Pressed()) && carBlackParked)
	{
		HandleCarLeft(&carBlackParked);	
	}
	else
	{
		return -1;
	}

	return 0;
}

