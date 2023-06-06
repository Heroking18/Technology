#pragma once
#include <cstdint>
#include "Button.h"
#include "Sensor.h"
#include "LED.h"
#include "Arduino.h"
//#define BUTTON_PRESSED 0xFFE0

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

