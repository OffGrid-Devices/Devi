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
	boolean state; // 0-released, 1-pressed
	boolean changed;
protected:
private:
	boolean val, _val = 1; 

//functions
public:
	Button();
	~Button();
	void init(byte p);
	void read();
	//boolean changed(); 
protected:
private:
	Button( const Button &c );
	Button& operator=( const Button &c );
	byte pin;
}; //Button

#endif //__BUTTON_H__
