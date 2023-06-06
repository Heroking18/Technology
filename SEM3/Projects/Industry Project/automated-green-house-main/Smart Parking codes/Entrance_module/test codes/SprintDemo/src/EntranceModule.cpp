#include "EntranceModule.h"

using namespace std;

EntranceModule::EntranceModule()
{
}

EntranceModule::EntranceModule(int LcdSclPin, int LcdSdaPin, int RfidSdaPin, int RfidRstPin, int ReserveRfidSdaPin, int ReserveRfidRstPin)
{
    entranceRfid = new EntranceGate(RfidSdaPin, RfidRstPin, 2);
    entranceLcd = new LCD(LcdSclPin, LcdSdaPin);
}

EntranceModule::~EntranceModule()
{
    // delete entranceRfid;
    // delete entranceReserveRfid;
    delete entranceLcd;
}

int EntranceModule::GetNumCarsParked() const
{
    return numCarsParked;
}

void EntranceModule::SetNumCarsParked(int count)
{
    numCarsParked = count;
}

int EntranceModule::GetNumCarsEntered() const
{
    return numCarsEntered;
}

void EntranceModule::SetNumCarsEntered(int count)
{
    numCarsEntered = count;
}

int EntranceModule::GetAvailableParkingSpots() const
{
    return availableParkingSpots;
}

void EntranceModule::SetAvailableParkingSpots(int count)
{
    availableParkingSpots = count;
}

int EntranceModule::GetTotalAvailableParkingSpots() const
{
    return totalAvailableParkingSpots;
}

void EntranceModule::SetTotalAvailableParkingSpots(int count)
{
    totalAvailableParkingSpots = count;
}

uint16_t EntranceModule::GetIP() const
{
    return IP;
}

// To be completed, returns 1 on tag scanned and 0 on failure
int EntranceModule::AssertRFID()
{
    return 0;
}

// To be completed
int EntranceModule::DisplayLCD(String cluster)
{
    // Shortest path
    entranceLcd->Display();

    return -1;
}