#include <SPI.h>
#include "mcp2515_can.h"

#define DEVICEA 0x43

const int spiCSPin = 10;
const int leftLEDPin = 2;
const int rightLEDPin = 4;

int ledState = LOW;

unsigned long previousMillis = 0;
unsigned long interval = 500;

mcp2515_can CAN(spiCSPin);

void setup()
{
  Serial.begin(115200);
  pinMode(leftLEDPin, OUTPUT);
  pinMode(rightLEDPin, OUTPUT);

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

    if (canId == DEVICEA) //ID of this device
    {
      if (buf == 108) // message: left, joystick turn left => blink right LED
      {
        if (millis() - previousMillis >= interval)
        {
          // if the LED is off turn it on and vice-versa:
          if (ledState == LOW)
            ledState = HIGH;
          else
            ledState = LOW;

          // set the LED with the ledState of the variable:
          digitalWrite(leftLEDPin, ledState);
          previousMillis = millis();
        }
      }
      else if (buf == 114) // message: right, joystick turn right blink right LED
      {
        if (millis() - previousMillis >= interval)
        {
          // if the LED is off turn it on and vice-versa:
          if (ledState == LOW)
            ledState = HIGH;
          else
            ledState = LOW;

          // set the LED with the ledState of the variable:
          digitalWrite(rightLEDPin, ledState);
          previousMillis = millis();
        }
      }
      else if (buf == 105) //message : idle, release joystick turn off LEDs
      {
        digitalWrite(leftLEDPin, LOW);
        digitalWrite(rightLEDPin, LOW);
      }
    }
  }
}