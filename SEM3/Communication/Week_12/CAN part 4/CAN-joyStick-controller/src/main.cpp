#include <Arduino.h>
#include <Wire.h>
#include "SparkFun_Qwiic_Joystick_Arduino_Library.h"
#include "mcp2515_can.h"

#define DEVICEA 0x43
#define DEVICEB 0x22

#define LEFT 600
#define RIGHT 300
#define UP 1023
#define DOWN 0
#define H_CENTRE 495
#define V_CENTRE 535

const int spiCSPin = 10;
uint16_t horizontal = 0; // default 495, full left 1023, full right 0
uint16_t vertical = 0;   // default 535, full up 1023, full down 0

mcp2515_can CAN(spiCSPin);
JOYSTICK joystick;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (CAN_OK != CAN.begin(CAN_500KBPS))
  {
    // Serial.println("CAN BUS Init Failed");
    delay(100);
  }
  Serial.println("CAN BUS  Init OK!");
  if (joystick.begin() == false)
  {
    Serial.println("Joystick does not appear to be connected. Please check wiring. Freezing...");
    while (1)
      ;
  }
}

unsigned char deviceAMsg[3] = {'l', 'r', 'i'}; // left, right, idle
unsigned char deviceBMsg[2] = {HIGH, LOW};     // On, Off

void loop()
{
  horizontal = joystick.getHorizontal();
  vertical = joystick.getVertical();
  Serial.println(joystick.getHorizontal());

  if (horizontal >= LEFT) // turn left, send to device A
  {
    CAN.sendMsgBuf(DEVICEA, 0, 1, deviceAMsg);
  }
  else if (horizontal <= RIGHT) // turn right, send to device A
  {
    CAN.sendMsgBuf(DEVICEA, 0, 1, (deviceAMsg + 1));
  }
  else if (horizontal == H_CENTRE || vertical == V_CENTRE) // idle, send to device A
  {
    CAN.sendMsgBuf(DEVICEA, 0, 1, (deviceAMsg + 2));
  }

  if (vertical == UP) // up, high beam on, send to device B
  {
    CAN.sendMsgBuf(DEVICEB, 0, 1, deviceBMsg);
  }
  else if (vertical == DOWN) // down, off, send to device B
  {
    CAN.sendMsgBuf(DEVICEB, 0, 1, (deviceBMsg + 1));
  }
}