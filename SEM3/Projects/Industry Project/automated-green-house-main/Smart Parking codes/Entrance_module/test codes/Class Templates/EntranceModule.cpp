#include "EntranceModule.h"
#include <iostream>

using namespace std;

EntranceModule::EntranceModule(int LcdSclPin, int LcdSdaPin, int RfidSdaPin, int RfidRstPin, int ReserveRfidSdaPin, int ReserveRfidRstPin)
{
    RFID entranceRfid = new RFID(RfidSdaPin, RfidRstPin);
    RFID entranceReserveRfid = new RFID(ReserveRfidSdaPin, ReserveRfidRstPin);
    LCD entranceLcd = new LCD(LcdSclPin, LcdSdaPin);
}

EntranceModule::~EntranceModule()
{
    delete entranceRfid;
    delete entranceReserveRfid;
    delete entranceLcd;
}

// To be completed
int EntranceModule::AssertRFID()
{
    return 0;
}

// To be completed
int EntranceModule::DisplayLCD()
{
    return 0;
}

int GetNumCarsParked() const
{
    return numCarsParked;
}

void SetNumCarsParked(int count) 
{
    numCarsParked = count;
}

int GetAvailableParkingSpots() const
{
    return availableParkingSpots;
}

void SetAvailableParkingSpots(int count)
{
    availableParkingSpots = count;
}

int GetTotalAvailableParkingSpots() const
{
    return totalAvailableParkingSpots;
}

void SetTotalAvailableParkingSpots(int count)
{
    totalAvailableParkingSpots = count;
}

uint8_t GetIP() const
{
    return IP;
}
