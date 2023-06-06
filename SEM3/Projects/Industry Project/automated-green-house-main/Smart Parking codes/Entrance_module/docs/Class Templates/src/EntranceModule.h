#ifndef __ENTRANCEMODULEH__
#define __ENTRANCEMODULEH__

#include "Arduino.h"
#include "RFID.h"
#include "LCD.h"
#include "cstddef"
#include <bitset>

class EntranceModule
{
private:
    int numCarsParked;
    int availableParkingSpots;
    int totalAvailableParkingSpots;
    int numCarsEntered;
    uint8_t IP;

    int AssertRFID();

public:
    EntranceModule(/* args */);
    ~EntranceModule();

    int getNumCarsParked()
    {
        return numCarsParked;
    }

    void setNumCarsParked(int count)
    {
        numCarsParked = count;
    }

    int getAvailableParkingSpots()
    {
        return availableParkingSpots;
    }

    void setAvailableParkingSpots(int count)
    {
        availableParkingSpots = count;
    }

    int getTotalAvailableParkingSpots()
    {
        return totalAvailableParkingSpots;
    }

    void setTotalAvailableParkingSpots(int count)
    {
        totalAvailableParkingSpots = count;
    }

    uint8_t getIP()
    {
        return IP;
    }
};

#endif