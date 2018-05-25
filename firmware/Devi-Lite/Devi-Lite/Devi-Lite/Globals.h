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

//! Total number of Modes
#define NUMMODES 4

//! Rotary switch lower split: number of pins connected to PORTC 
#define ROTLOWER 8
//! Rotary switch upper split: number of pins connected to PORTD
#define ROTUPPER 4

#define bit_get(p,m) ((p) & (m))
#define bit_set(p,m) ((p) |= (m))
#define bit_clear(p,m) ((p) &= ~(m))
#define BIT(x)(0x01 << (x))

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif


/*! \defgroup UI
* User interface variables
*  @{
*/

/*! \brief 8-bit variable containing all 8 buttons values.
* 
* Button 1 is on bit0, button 6 is on bit5, Function button is on bit6 and Mode button is on bit7.
*/
uint8_t buttons;
/*! Previous buttons' values for state change detection*/ 
uint8_t _buttons; 

//! Rotary switch value from 0 to 11
uint8_t rotary;  

//! Knobs array with values from 0 to 127
uint8_t knobs[NUMVOICES];

//! Mode variable set by mode button 
uint8_t mode;
/*! \brief Mode led (rgb) colors
*
* I made a mistake in the schematic: the green and blue pins are switched.
*\n So the byte representation is 00GBR000.
*/
uint8_t modeColors[NUMMODES] = {B00100000, B00010000, B00111000, B00001000}; 
							  //green,     blue,      white,     red
 
/*! @} */ // end of UI variables 


#endif /* GLOBALS_H_ */