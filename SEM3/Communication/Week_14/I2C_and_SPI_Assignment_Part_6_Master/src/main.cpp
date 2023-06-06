#include <Arduino.h>
#include <SPI.h>

void setup(void)
{

  digitalWrite(SS, HIGH); // ensure SS stays high for now
  Serial.begin(115200);
  // Put SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin();

  // Slow down the master a bit
  SPI.setClockDivider(SPI_CLOCK_DIV8);

} // end of setup

void loop(void)
{

  char c;

  // enable Slave Select
  digitalWrite(SS, LOW); // SS is pin 10

  if (Serial.available() > 0)
  {
    c = Serial.read();
    SPI.transfer(c);
    Serial.println(c);
  }

  // disable Slave Select
  digitalWrite(SS, HIGH);
} // end of loop