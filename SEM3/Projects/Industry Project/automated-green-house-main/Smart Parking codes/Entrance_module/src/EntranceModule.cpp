/**
 * @file EntranceModule.cpp
 * @authors 
 * Sean-David Brokke (4208501)
 * Nick Mulders (4523504​)
 * 
 * @brief 
 * @version 0.1
 * @date 2023-01-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "EntranceModule.h"
using namespace std;

/**
 * @brief Construct a new Entrance Module:: Entrance Module object
 * 
 * Constructor creates 1 object of LCD and 2 Gates which are RFID sensors, 
 * because the Entrance Module consists of 1 lcd screen and 2 rfid sensors
 * 
 * @param LcdSclPin 
 * @param LcdSdaPin 
 * @param RfidSdaPin1 Entrance Gate RFID SDA pin
 * @param RfidRstPin1 Entrance Gate RFID RST pin
 * @param RfidSdaPin2 Exit Gate RFID SDA pin
 * @param RfidRstPin2 Exit Gate RFID RST pin
 */
EntranceModule::EntranceModule(int LcdSclPin, int LcdSdaPin, int RfidSdaPin1, int RfidRstPin1,  int RfidSdaPin2, int RfidRstPin2) 
:numCarsEntered(0),
availableParkingSpots(0),
totalAvailableParkingSpots(0),
numCarsParked(0)
{
    gateLCD = new LCD(LcdSclPin, LcdSdaPin);
    entranceGate = new Gate(RfidSdaPin1, RfidRstPin1, ENTRANCE_GATE_LED);
    exitGate = new Gate(RfidSdaPin2, RfidRstPin2, EXIT_GATE_LED);
}

EntranceModule::~EntranceModule()
{
    delete gateLCD;
    delete entranceGate;
    delete exitGate;
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

/**
 * @brief 
 * 
 * @return int exit, entered  or no cars detected state
 */
int EntranceModule::CheckGate()
{
    if (exitGate->GateState() == OPEN)
    {
        if(GetNumCarsEntered() > 0)
        {
            numCarsEntered--;
            return CAR_HAS_LEFT;
        }
    }
    if (entranceGate->GateState() == OPEN)
    {
        if(GetNumCarsEntered() < GetTotalAvailableParkingSpots())
        {
            numCarsEntered++;
            return CAR_ENTERED;
        }
    }
    return NO_CARD_DETECTED;
}

int EntranceModule::DisplayLCD(String msg)
{
    gateLCD->Display(msg);
    return 0;
}
