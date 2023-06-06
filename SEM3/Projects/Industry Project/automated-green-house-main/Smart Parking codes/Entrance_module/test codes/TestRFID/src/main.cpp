#include <Arduino.h>
#include "EntranceGate.h"
#define SS_PIN_1 5
#define RST_PIN_1 27

#define SS_PIN_2 15
#define RST_PIN_2 4

Gate gateEntrance(SS_PIN_1,RST_PIN_1,25);
Gate gateExit(SS_PIN_2,RST_PIN_2,26);
void setup()
{
  Serial.begin(115200);
}

void loop()
{
  Serial.println(gateEntrance.GateState());
  gateExit.GateState();
}