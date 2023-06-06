#include <Arduino.h>
#include "SPI.h"
#include "mcp2515_can.h"

#define MSG_SIZE 3
const int spiCSPin = 10; // Replace CCC by actual Slave Select pin
unsigned char msg[MSG_SIZE];
int arraySize = 0;

mcp2515_can CAN(spiCSPin);

void setup()
{
  Serial.begin(115200);
  while (CAN_OK != CAN.begin(CAN_500KBPS))
  {
    Serial.println("CAN BUS init Failed");
    delay(100);
  }
  Serial.println("CAN BUS Shield Init OK!");
}

void loop()
{
  // This checks if the serial monitor is receiving any characters
  if (Serial.available() > 0)
  {
    arraySize = Serial.readBytesUntil('\n', msg, MSG_SIZE);
  }
  CAN.sendMsgBuf(0x43, 0, arraySize, msg);
  delay(1000);
}