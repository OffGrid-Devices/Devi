/*!
* \file Globals.h
* \brief Global variables.
* To be used by all classes
*
*/

#ifndef GLOBALS_H_
#define GLOBALS_H_

//! Control update rate in Hertz (must be a power of 2)
#define CONTROL_RATE 512

/*! 8-bit variable containing all 8 buttons values.
* 
* Button 1 is on bit0, button 6 is on bit5, Function button is on bit6 and Mode button is on bit7.
*/
uint8_t buttons; 


#endif /* GLOBALS_H_ */