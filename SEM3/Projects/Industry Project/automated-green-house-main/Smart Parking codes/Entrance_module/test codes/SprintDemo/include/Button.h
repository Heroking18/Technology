#pragma once

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <Arduino.h>

#define BUTTON_PRESSED 0xE000

class Button 
{
  private:
    int buttonPin;
    uint16_t state;

  public:
    Button(int);
    ~Button();
    uint16_t Debounce();
    bool Pressed();
};