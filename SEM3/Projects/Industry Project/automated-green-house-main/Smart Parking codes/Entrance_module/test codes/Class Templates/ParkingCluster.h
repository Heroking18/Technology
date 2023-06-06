#pragma once
#include <cstddef>

class ParkingCluster
{
private:
    int NumCarsParked;
    int AvailableParkingSpots;
    int TotalAvailableParkingSpots;
    int NumCarsEntered;
    bool carParked = false;
    int ToggleLED();
    int DetermineCarParked();
    byte IP;
    
public:
    ParkingCluster(int, int, int);
    ~ParkingCluster();
    int GetNumCarsParked() const;
 	int GetAvailableParkingSpots() const;
 	int GetNumCarsENtered() const;
 	byte GetIP() const;
 	int GetTotalAvailableParkingSpots() const;
 	void SetNumCarsParked(int CarsParked);
 	void SetNumCarsEntered(int CarsEntered);
 	void SetTotalAvailableParkingSpots(int AvailableSpots);
 	
};

