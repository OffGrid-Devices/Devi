/* 
* Button.h
*
* Created: 15-04-2018 12:05:15
* Author: tiago
*/


#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "Arduino.h"

class Button
{
//variables
public:
protected:
private:

//functions
public:
	Button();
	~Button();
	void init(byte p);
	boolean getState(); 
protected:
private:
	Button( const Button &c );
	Button& operator=( const Button &c );
	byte pin;
}; //Button

#endif //__BUTTON_H__
