#include <Arduino.h>
#include "ParkingCluster.h"
#define LDRPIN 5
#define PRESSUREPIN 18
#define REDLIGHTPIN 18 
#define GREENLIGHTPIN 19 
#define BLUELIGHTPIN 21

ParkingCluster *cluster;//Change the pins at home

void setup() {
  // put your setup code here, to run once:
  pinMode(REDLIGHTPIN, OUTPUT);
  pinMode(GREENLIGHTPIN, OUTPUT);
  pinMode(BLUELIGHTPIN, OUTPUT);
  cluster = new ParkingCluster(LDRPIN, PRESSUREPIN, REDLIGHTPIN, GREENLIGHTPIN, BLUELIGHTPIN);
}

void loop() {
  // put your main code here, to run repeatedly:
  cluster->ChangeLedColour();
}