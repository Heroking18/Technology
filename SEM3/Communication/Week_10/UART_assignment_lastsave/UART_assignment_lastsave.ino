#include "header.h"

void setup() {
  pinMode(RXpin, INPUT);
  pinMode(LED_SUCCESS, OUTPUT);
  pinMode(LED_ERROR, OUTPUT);
  Serial.begin(1200);
  state = INIT;
}

void loop() {

  switch (state)
  {
    case INIT:
      reset_state();
      break;
    case NO_DETECTION:
      idle_state();
      break;
    case MESSAGE_READ:
      receive_message();
      break;
    case PARITY_CALC:
      parity();
      break;
    case TEST:
      test_message();
      break;
    case ERROR_MESSAGE:
      error_message();
      break;
  }
}

// Reset all the variables
void reset_state(void)
{
  val = 0;
  count = 0;
  counter = 0;
  parity_calc = 0;
  state = NO_DETECTION;
}

// Waiting for incoming messages from the receive pin
void idle_state(void)
{
  if (micros() - previousMicros_NO_DETECTION >= interval_NO_DETECTION)
  {
    previousMicros_NO_DETECTION = micros();
    val = digitalRead(RXpin); // RXpin is always high when idle
    if (val == 0)
    {
      state = MESSAGE_READ;
    }
  }
}

// Store message inside a variable
void receive_message(void)
{
  if (micros() - previousMicros_MESSAGE_READ >= interval_MESSAGE_READ)
  {
    previousMicros_MESSAGE_READ = micros();
    if (count > MAX_BIT_SIZE)
    {
      state = PARITY_CALC;
    }
    else
    {
      bit_val = digitalRead(RXpin);
      res[count] = bit_val;
      count++;
      return;
    }
  }
}

// Count the high bits in the byte
void parity(void)
{
  if (micros() - previousMicros_CALC >= interval_CALC)
  {
    previousMicros_CALC = micros();
    while (counter < MAX_BIT_SIZE)
    {
      if (res[counter] == 1)
      {
        parity_calc++;
      }
      counter++;
    }
    parity_calc--;  // remove the stop bit
  }

  if ((parity_calc % 2) == 0)
  {
    state = TEST;
  }
  else
  {
    state = ERROR_MESSAGE;
  }
}

// Test message if received correctly
void test_message(void)
{
  if (micros() - previousMicros_CALC >= interval_CALC)
  {
    previousMicros_CALC = micros();
    for (uint8_t i = 9; i > 1; i--)
    {
      test_byte |= res[i];
      test_byte = (test_byte << 1);
    }
    Serial.println(test_byte);
    if (test_byte == CHAR_D)
    {
      digitalWrite(LED_SUCCESS, HIGH);
      state = INIT;
    }
    else if (test_byte == CHAR_B)
    {
      digitalWrite(LED_SUCCESS, LOW);
      state = INIT;
    }
    else
    {
      state = ERROR_MESSAGE;
    }
  }
}

// Notify user of corrupted message
void error_message(void)
{
  digitalWrite(LED_ERROR, HIGH);
  delay(1000);
  digitalWrite(LED_ERROR, LOW);
  state = INIT;
}
