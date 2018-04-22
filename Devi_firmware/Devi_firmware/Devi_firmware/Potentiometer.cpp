/*
* Potentiometer.cpp
*
* Created: 22-04-2018 04:50:15
* Author: tiago
*/

#pragma GCC push_options
#pragma GCC optimize (OPTIMIZATION)

#include "Potentiometer.h"

// default constructor
Potentiometer::Potentiometer()
{
} //Potentiometer

// default destructor
Potentiometer::~Potentiometer()
{
} //~Potentiometer

void Potentiometer::init(byte p){
	pin = p;
}

void Potentiometer::read(){
	val = mozziAnalogRead(pin) >> 3; // 0..127
	if ( val != _val )   changed = true;
	else   changed = false;
	_val = val;
}

#pragma GCC pop_options