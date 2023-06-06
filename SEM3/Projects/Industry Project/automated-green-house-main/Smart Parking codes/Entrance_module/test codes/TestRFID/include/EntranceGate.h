#pragma once
// #ifndef _ENTRANCEGATE_H
// #define _ENTRANCEGATE_H

#include "Arduino.h"
#include <SPI.h>
#include <MFRC522.h>


#define ERROR_ -1
#define SUCCESS 0
#define OPEN 1
#define CLOSED 0
#define INTERVAL_GATE 5000

typedef enum 
{
    IDLE,
    CARD_DETECTED,
    RESET
}States;

class Gate
{
private:
    int ledPin;
    unsigned long previousTime;
    MFRC522::MIFARE_Key key;
    MFRC522 rfid;
    States state;
public:
    Gate(int, int, int);
    ~Gate();
    int readRFID();
    int GateState();
    int OpenGate();
    int CloseGate();
    bool GateIsOpen();
};

// #endif