#include "Button.h"

using namespace std;


Button::Button(int BtnPin)
{
    buttonPin = BtnPin;
    state = 0;
    pinMode(buttonPin, INPUT_PULLUP);
}

Button::~Button()	
{
}



/**
 * @brief Debouncer using  bit shifting
 * 
 * @return uint16_t Value of button state.
 */
uint16_t Button::Debounce()
{
  state = 0; //static means there is 1 variable available for everyone(reserved only for this function)
  state = (state << 1) | digitalRead(buttonPin) | BUTTON_PRESSED; // A beautiful press will result in the 16bit int being 0xFF00, (0XFE00)
  return state;  // if there is bouncig result will be something like: 01010 1100 01010 01011 
}

bool Button::Pressed()
{
  return (Debounce() == BUTTON_PRESSED);
}
