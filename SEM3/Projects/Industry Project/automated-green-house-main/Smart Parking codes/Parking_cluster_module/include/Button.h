/**
 * @file Button.h
 * @author Sean-David Brokke (4208501)
 * @brief 
 * @version 0.1
 * @date 2023-01-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
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