#ifndef __PARKINGCLUSTERH__
#define __PARKINGCLUSTERH__
#include <cstddef>

class ParkingCluster
{
private:
    int numCarsParked;
    int availableParkingSpots;
    int totalAvailableParkingSpots;
    int numCarsEntered;
    int toggleLED();
    int determineCarParked();
    byte IP;
    Sensor sensor;
    LED ledElement;
public:
    ParkingCluster();
    ~ParkingCluster();
    int getNumCarsParked();
 	int getAvailableParkingSpots();
 	int getNumCarsENtered();
 	byte getIP();
 	int getTotalAvailableParkingSpots();
 	void setNumCarsParked(int carsParked);
 	void setNumCarsEntered(int carsEntered);
 	void setTotalAvailableParkingSpots(int availableSpots);
 	
};

#endif

