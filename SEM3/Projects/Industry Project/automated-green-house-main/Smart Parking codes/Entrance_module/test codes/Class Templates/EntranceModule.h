#pragma once
#include "Arduino.h"
#include "cstddef"
#include <bitset>

class EntranceModule
{
private:
    int numCarsParked;
    int availableParkingSpots;
    int totalAvailableParkingSpots;
    int numCarsEntered;
    byte IP;

    int AssertRFID();
    int DisplayLCD();

public:
    EntranceModule(int, int, int, int, int, int) = default;
    ~EntranceModule();
    int GetNumCarsParked() const;
    int GetAvailableParkingSpots() const;
    int GetTotalAvailableParkingSpots() const;
    int GetNumCarsEntered() const;
    byte GetIP() const;
    void SetNumCarsParked(int);
    void SetNumCarsEntered(int);
    void SetTotalAvailableParkingSpots(int);
};
