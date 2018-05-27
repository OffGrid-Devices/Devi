/* 
* Button.cpp
*
* Created: 15-04-2018 12:05:15
* Author: tiago
*/


#pragma GCC push_options
#pragma GCC optimize (OPTIMIZATION)

#include "Button.h"

// default constructor
Button::Button()
{
} //Button

// default destructor
Button::~Button()
{
} //~Button

void Button::init(byte p){
  pin = p;
  pinMode(pin, INPUT);
}
void Button::read(){
  val = digitalRead(pin);
  if ( val != _val){
    changed = true;
    if(val < _val) state = 1; //pressed
    else state = 0; //released
  }
  else
  {
    changed = false;
  }
  
  _val = val; 
}

#pragma GCC pop_options
