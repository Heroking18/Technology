#pragma once
#include "painlessMesh.h"
#include "EntranceGate.h"
#include <iostream>
#include "LCD.h"
#include "Arduino.h"
#include <cstdint>


class EntranceModule
{
private:
    LCD *entranceLcd;
    EntranceGate *entranceRfid;
    EntranceGate *entranceReserveRfid;
    int numCarsParked;
    int availableParkingSpots;
    int totalAvailableParkingSpots;
    int numCarsEntered;
    uint16_t IP;
    const int INTERVAL100 = 100;
    unsigned long previousTime = 0;

public:
    EntranceModule();
    EntranceModule(int, int, int, int, int, int);
    ~EntranceModule();
    int GetNumCarsParked() const;
    int GetAvailableParkingSpots() const;
    int GetTotalAvailableParkingSpots() const;
    int GetNumCarsEntered() const;
    uint16_t GetIP() const;
    void SetNumCarsParked(int);
    void SetNumCarsEntered(int);
    void SetTotalAvailableParkingSpots(int);
    void SetAvailableParkingSpots(int);
    int AssertRFID();
    int DisplayLCD(String);
};
