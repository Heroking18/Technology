/**
 * @file ParkingCluster.h
 * @authors
 * Sean-David Brokke (4208501)
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
#pragma once
#include <cstdint>
#include "Button.h"
#include "Sensor.h"
#include "LED.h"
#include "Arduino.h"

/*---------------Communication using mesh--------------*/
#define MESH_PREFIX "SmartParking"
#define MESH_PASSWORD "fontys123"
#define MESH_PORT 5555
#define BUF_LEN 256

/*---------------Change Pins--------------*/
#define REDLIGHTPIN 18
#define GREENLIGHTPIN 19
#define BLUELIGHTPIN 21
#define PRESSUREPIN 35
#define YELLOWBUTTONPIN 33
#define REDBUTTONPIN 23
#define BLUEBUTTONPIN 22
#define BLACKBUTTONPIN 15
#define LDRPIN 34

//class Sensor;
//class LED;
//class Button;

class ParkingCluster
{
private:
    Sensor *clusterLdr;
	Sensor *clusterPressure;
	LED *clusterLED;
    Button *YellowButton;
    Button *RedButton;
    Button *BlueButton;
    Button *BlackButton;
    

    int NumCarsParked;
    int AvailableParkingSpots;
    int TotalAvailableParkingSpotsInCluster;
    int NumCarsEntered;
    bool carSensorParked = false;
    bool carYellowParked = false;
    bool carRedParked = false;
    bool carBlueParked = false;
    bool carBlackParked = false;
    uint16_t IP;
    
public:
    ParkingCluster(int, int, int, int, int, int, int, int, int);
    ~ParkingCluster();
    int GetNumCarsParked() const;
 	int GetAvailableParkingSpotsInCluster() const;
 	int GetTotalAvailableParkingSpotsInGarage() const;
 	int GetNumCarsEntered() const;
 	uint16_t GetIP() const;
 	void SetNumCarsParked(int CarsParked);
 	void SetNumCarsEntered(int CarsEntered);
 	void SetTotalAvailableParkingSpotsInCluster(int AvailableSpots);
    int ChangeLedColour();
    int DetermineCarParked();
    void HandleCarParked(bool*);
    void HandleCarLeft(bool*);
 	
};

