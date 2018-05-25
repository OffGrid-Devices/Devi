/*!
* \file Globals.h
* \brief Global variables.
* To be used by all classes
*
*/

#ifndef GLOBALS_H_
#define GLOBALS_H_

//! Control update rate in Hertz (must be a power of 2).
#define CONTROL_RATE 512

//! Compiler optimization flag
#define OPTIMIZATION "O3"

//! Total number of voices. This value will be often used as there are not only 6 voices, but 6 leds, 6 potentiometers, etc.
#define NUMVOICES 6

/*! 8-bit variable containing all 8 buttons values.
* 
* Button 1 is on bit0, button 6 is on bit5, Function button is on bit6 and Mode button is on bit7.
*/
uint8_t buttons; 


#endif /* GLOBALS_H_ */