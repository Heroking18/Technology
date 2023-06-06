#include <SPI.h>
#include "mcp2515_can.h"

const int spiCSPin = 10;
const int LEDPin = 2;

#define DEVICEB 0x22

mcp2515_can CAN(spiCSPin);

void setup()
{
  Serial.begin(115200);
  pinMode(LEDPin, OUTPUT);

  while (CAN_OK != CAN.begin(CAN_500KBPS))
  {
    Serial.println("CAN BUS Init Failed");
    delay(100);
  }
  Serial.println("CAN BUS  Init OK!");
}

void loop()
{
  unsigned char len = 0; // read buffer length
  unsigned char buf;  // buffer to save the read byte

  if (CAN_MSGAVAIL == CAN.checkReceive())
  {
    CAN.readMsgBuf(&len, &buf);

    unsigned long canId = CAN.getCanId();

    if (canId == DEVICEB)//this device ID
    {
      if (buf == 0x1) // message: on, if joystick turn up all the way => LED ON
      {
        digitalWrite(LEDPin, HIGH);
      }
      else if (buf == 0x0) //message : off , if joystick turn down all the way => LED OFF
      {
        digitalWrite(LEDPin, LOW);
      }
    }
  }
}