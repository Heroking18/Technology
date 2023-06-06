/**
 * @file EntranceModule.h
 * @authors
 * Sean-David Brokke (4208501)
 * Mitchell van ‘t Kruys (4058151​)
 * Nick Mulders (4523504​)
 * @brief 
 * @version 0.1
 * @date 2023-01-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "painlessMesh.h"
#include "Gate.h"
#include "Arduino.h"
#include <cstdint>
#include <iostream>
#include "LCD.h"
//#include "Arduino.h"

/*---------------Communication using mesh--------------*/
#define MESH_PREFIX "SmartParking"
#define MESH_PASSWORD "fontys123"
#define MESH_PORT 5555
#define BUF_LEN 256

//LCD
#define LCDSCLPIN 22
#define LCDSDAPIN 21

//RFID
#define RFID_SDA_PIN_1 5
#define RFID_RST_PIN_1 27
#define RFID_SDA_PIN_2 15
#define RFID_RST_PIN_2 4

#define CAR_HAS_LEFT 2
#define CAR_ENTERED 1
#define NO_CARD_DETECTED 0

//Leds that simulate gates
#define ENTRANCE_GATE_LED 25
#define EXIT_GATE_LED 26


/*-----------------------------*/


class EntranceModule
{
private:
    LCD *gateLCD;
    Gate *entranceGate;
    Gate *exitGate;
    int numCarsParked;
    int availableParkingSpots;
    int totalAvailableParkingSpots;
    int numCarsEntered;
    uint16_t IP;

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
    int CheckGate();
    int DisplayLCD(String);
};
