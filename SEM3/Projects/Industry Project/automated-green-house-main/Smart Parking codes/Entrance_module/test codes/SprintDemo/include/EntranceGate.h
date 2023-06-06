#pragma once

#include "Arduino.h"
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5
#define RST_PIN 27
#define ERROR -1
#define SUCCESS 0
#define INTERVAL_EG 5000

typedef enum 
{
    IDLE,
    CARD_DETECTED,
    RESET
}States;

class EntranceGate
{
private:
    int ledState;
    int ledPin;
    unsigned long previousTime;
    MFRC522::MIFARE_Key key;
    MFRC522 rfid;
    States state;
public:
    EntranceGate(int, int, int);
    ~EntranceGate();
    int readRFID();
    int GateState();
    int openGate();
    int closeGate();
};
