#include "EntranceGate.h"
#include <iostream>

using namespace std;

EntranceGate::EntranceGate(int SDA, int RST, int ledpin)
    : state(IDLE),
      ledState(LOW),
      previousTime(0)
{
  this->ledPin = ledpin;
  rfid = MFRC522(SDA, RST);
  SPI.begin();
  rfid.PCD_Init();
  rfid.PCD_DumpVersionToSerial();
  pinMode(ledPin, OUTPUT);
}

EntranceGate::~EntranceGate()
{
}

int EntranceGate::readRFID()
{ /* function readRFID */
  ////Read RFID card
  for (byte i = 0; i < 6; i++)
  {
    key.keyByte[i] = 0xFF;
  }
  // Look for new 1 cards

  if (!rfid.PICC_IsNewCardPresent())
  {
    return ERROR;
  }

  // Verify if the NUID has been readed
  if (!rfid.PICC_ReadCardSerial())
  {
    return SUCCESS;
  }
}

int EntranceGate::openGate()
{
  digitalWrite(ledPin, HIGH);
  return 1;
}

int EntranceGate::closeGate()
{
  digitalWrite(ledPin, LOW);
  return 0;
}

int EntranceGate::GateState()
{
  int gateState = 0;
  switch (state)
  {
  case IDLE:
    // Serial.println("IN IDLE");
    if (readRFID() == SUCCESS)
    {
      // Serial.println("SUCCESS");
      state = CARD_DETECTED;
    }
    break;
  case CARD_DETECTED:
    // Serial.println("IN CARD_DETECTED");
    gateState = openGate();
    if (millis() - previousTime >= INTERVAL_EG)
    {
      previousTime = millis();
      gateState = openGate();
      // Serial.println(previousTime);
      state = RESET;
    }
    break;
  case RESET:
    gateState = closeGate();
    state = IDLE;
    break;
  }

  return gateState;
}