#include <Arduino.h>
#include <Wire.h>

#define JOYSTICK_ADDR 0x20 // I2C address of the STTS751 temperature sensor

// Joystick
#define CURRENT_HORIZONTAL_POSITION_MSB 0x03
#define CURRENT_HORIZONTAL_POSITION_LSB 0x04
#define CURRENT_VERTICAL_POSITION_MSB 0x05
#define CURRENT_VERTICAL_POSITION_LSB 0x06

// Temperature
#define STTS751_ADDR 0x4A // I2C address of the STTS751 temperature sensor
#define Temperature_value_high_byte_ADD 0x00
#define Temperature_value_low_byte_ADD 0x02

float tempC = 0;

uint8_t STTS751_read(uint8_t reg)
{
  Wire.beginTransmission(JOYSTICK_ADDR); // set the I2C address of the sensor
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(JOYSTICK_ADDR, 1); // request 2 bytes of data from the sensor
  return Wire.read();
}

uint16_t Joystick_horizontal()
{
  uint16_t horizontal_MSB = STTS751_read(CURRENT_HORIZONTAL_POSITION_MSB);
  uint16_t horizontal_LSB = STTS751_read(CURRENT_HORIZONTAL_POSITION_LSB);
  return ((horizontal_MSB << 8) | horizontal_LSB) >> 6;
}

uint16_t Joystick_vertical()
{
  uint16_t vertical_MSB = STTS751_read(CURRENT_VERTICAL_POSITION_MSB);
  uint16_t vertical_LSB = STTS751_read(CURRENT_VERTICAL_POSITION_LSB);
  return ((vertical_MSB << 8) | vertical_LSB) >> 6;
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
  temp = tempHighByte + ((tempLowByte >> 4) / 16.0);

  // convert the temperature value to degrees Celsius
  return tempC = (float)temp;
}

void setup()
{
  Wire.begin(); // initialize I2C communication
  Serial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:
  uint16_t horizontal_value = Joystick_horizontal();
  uint16_t vertical_value = Joystick_vertical();

  // Serial.println(horizontal_value); // 1023
  // Serial.println(vertical_value);

  if (horizontal_value == 1023)
  {
    float temp_val = Temperature_sensor();
    Serial.println(temp_val);
  }
  else if (horizontal_value == 0)
  {
    Serial.println("Part 2");
  }
}
