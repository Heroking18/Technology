#ifndef _HEADER_H
#define _HEADER_H 

//DEFINES
#define MAX_BIT_SIZE 10
#define PARITY_BIT 9
#define BYTE_SIZE 9
#define CHAR_D 0b01000100
#define CHAR_B 0b01000010

enum State {
  INIT,
  NO_DETECTION,
  MESSAGE_READ,
  PARITY_CALC,
  TEST,
  ERROR_MESSAGE
};
State state;

//PINS
const int RXpin = 0;
const int LED_SUCCESS = 3;
const int LED_ERROR = 2;

//VARIABLES
uint16_t val;
uint16_t res[MAX_BIT_SIZE];
uint8_t bit_val = 0;
uint8_t test_byte;
uint8_t count = 0;
uint8_t counter = 1;
uint8_t parity_calc = 0;

//TIMERS
unsigned long interval_NO_DETECTION = 833;
unsigned long previousMicros_NO_DETECTION = 0;

unsigned long interval_MESSAGE_READ = 860;
unsigned long previousMicros_MESSAGE_READ = 0;

unsigned long interval_CALC = 200000;
unsigned long previousMicros_CALC = 0;

unsigned long interval_TEST = 200000;
unsigned long previousMicros_TEST = 0;

#endif
