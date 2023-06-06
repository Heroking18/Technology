#include "EntranceGate.h"
#include <iostream>

using namespace std;

Gate::Gate(int SDA, int RST, int ledpin)
{
  state = IDLE;
  previousTime = 0;
  this->ledPin = ledpin;
  rfid = MFRC522(SDA, RST);
  SPI.begin();
  rfid.PCD_Init();
  rfid.PCD_DumpVersionToSerial();
  pinMode(ledPin, OUTPUT);
}



int Gate::readRFID()
{ /* function readRFID */
  ////Read RFID card
  for (byte i = 0; i < 6; i++)
  {
    key.keyByte[i] = 0xFF;
  }
  // Look for new 1 cards

  if (!rfid.PICC_IsNewCardPresent())
  {
    return ERROR_;
  }

  // Verify if the NUID has been readed
  if (!rfid.PICC_ReadCardSerial())
  {
    return SUCCESS;
  }
}

int Gate::OpenGate()
{
  digitalWrite(ledPin, HIGH);
  return OPEN;
}

int Gate::CloseGate()
{
  digitalWrite(ledPin, LOW);
  return CLOSED;
}

int Gate::GateState()
{
  int gateState = 0;
  switch (state)
  {
  case IDLE:
    //Serial.println("IN IDLE");
    if (readRFID() == SUCCESS)
    {
      //Serial.println("SUCCESS");
      state = CARD_DETECTED;
    }
    break;
  case CARD_DETECTED:
    //Serial.println("IN CARD_DETECTED");
    gateState = OpenGate();
    if (millis() - previousTime >= INTERVAL_GATE)
    {
      previousTime = millis();
      gateState = OpenGate();
      //Serial.println(previousTime);
      state = RESET;
    }
    break;
  case RESET:
    gateState = CloseGate();
    state = IDLE;
    break;
  }

  return gateState;
}

bool Gate::GateIsOpen()
{
  return (GateState() == OPEN);
}

Gate::~Gate()
{
}