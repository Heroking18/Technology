#include <Wire.h>
#include <Arduino.h>

#define Product_ID_register 0xFD
#define STTS751_ADDR 0x4A // I2C address of the STTS751 temperature sensor
#define Temperature_value_high_byte_ADD 0x00
#define Temperature_value_low_byte_ADD 0x02

float tempC = 0;
uint8_t sensorID;

uint8_t STTS751_read(uint8_t reg)
{
  Wire.beginTransmission(STTS751_ADDR); // set the I2C address of the sensor
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(STTS751_ADDR, 1); // request 2 bytes of data from the sensor
  return Wire.read();
}

float Temperature_sensor()
{
  int temp = 0;
  uint8_t tempLowByte = 0;
  uint8_t tempHighByte = 0;

  // read the temperature data from the sensor
  tempHighByte = STTS751_read(Temperature_value_high_byte_ADD);
  tempLowByte = STTS751_read(Temperature_value_low_byte_ADD);

  // combine the low and high bytes to get the full temperature value
  temp = (tempHighByte + ((tempLowByte >> 4) / 16.0));

  return tempC = (float)temp;
}

void setup()
{
  Wire.begin(); // initialize I2C communication
  Serial.begin(9600);
  Serial.print("Sensor ID: ");
  Serial.println(sensorID);
}

void loop()
{
  float temp_val = Temperature_sensor();
  sensorID = STTS751_read(Product_ID_register);

  // print the temperature and ID value to the serial monitor
  Serial.println(temp_val);

  delay(500); // wait 1 second before reading the temperature again
}
