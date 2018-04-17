/* 
* Button.cpp
*
* Created: 15-04-2018 12:05:15
* Author: tiago
*/


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
	pinMode(p, INPUT);
}

boolean Button::getState(){
	return  digitalRead(pin);
}