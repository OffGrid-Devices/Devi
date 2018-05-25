/*!
* \file Globals.h
* \brief Global variables.
* To be used by all classes
*
*/

#ifndef GLOBALS_H_
#define GLOBALS_H_

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


//! Control update rate in Hertz (must be a power of 2).
#define CONTROL_RATE 512

//! Compiler optimization flag
#define OPTIMIZATION "O3"

//! Total number of Modes
#define NUMMODES 4

//! Rotary switch lower split: number of pins connected to PORTC 
#define ROTLOWER 8
//! Rotary switch upper split: number of pins connected to PORTD
#define ROTUPPER 4

//! Total number of voices. This value will be often used as there are not only 6 voices, but 6 leds, 6 potentiometers, etc.
#define NUMVOICES 6

//! Minimum pitch 
#define MINPITCH 24

//! Minimum BPM
#define MINBPM 40

//! Minimum filter frequency
#define MINFILTER 40
//! Maximum filter frequency
#define MAXFILTER 12000

/*! \defgroup UI
* User interface variables
*  @{
*/

/*! \brief 8-bit variable containing all 8 buttons values.
* 
* Button 1 is on bit0, button 6 is on bit5, Function button is on bit6 and Mode button is on bit7.
*/
uint8_t buttons = B11111111;
/*! Previous buttons' values for state change detection*/ 
uint8_t _buttons; 

//! Rotary switch value from 0 to 11
uint8_t rotary; 

//! Previous RotarySwitch value for state change detection
uint8_t _rotary; 

//! Knobs array with values from 0 to 255
uint8_t knobs[NUMVOICES];

//! Previous knob values for state change detection
uint8_t _knobs[NUMVOICES];

//! Mode variable set by mode button 
uint8_t mode;

//! Mode button locked?
boolean modeLock = false;
//! Previous Mode lock
boolean _modeLock = true;
//! Function button locked ? 
boolean functionLock = false; 
//! Previous Function lock
boolean _functionLock = true;

/*! \brief Mode led (rgb) colors
*
* I made a mistake in the schematic: the green and blue pins are switched.
*\n So the byte representation is 00GBR000.
*/
uint8_t modeColors[NUMMODES] = {B00100000, B00010000, B00111000, B00001000}; 
							  //green,     blue,      white,     red
 
/*! @} */ // end of UI variables 

/*! \defgroup Sequencer
*
* Sequncer Mode variables.
*  @{
*/

//! \brief Step mutes
//boolean stepMute[6] = {false, false, false, false, false, false};
uint8_t stepMutes = B00000000; 
//! \brief Current sequencer step
int8_t step = 0;
//! \brief Selected number of steps
uint8_t steps = 6; // selected number of steps
//! \brief Beat subdivisions (x1, x2, x4, x8, x32, x64)
uint8_t subdivisions[8] {1, 2, 4, 8, 16, 32, 64, 128};
//! \brief Selected subdivision
uint8_t subdivision = 2; 
//! \brief Beats per minute
uint16_t bpm = 120;
//! \brief Previous beats per minute
uint16_t _bpm = bpm;
/*! \brief Sequencer toggle (On/Off) 
*
* Note that the sequencer can be kept running while throughout all Modes. 
*/
boolean seqOnOff = true; 
/*! \brief Sequencer clock signal 
*
* The sequencer actually runs at twice the audible sequencer rate to turn bpm led indicator on/off (1-triggers envelopes and led on; 0- triggers led off)
*/
boolean seqTrigger = 1; 
//! Metronome
Metronome metro(60000/bpm/2); // calculate bpm
//! Step mode ( up, down, up&down, palindrome, random step, random step & random pitch amount)
uint8_t stepMode = 0;
//! Sequencer direction
boolean stepDir = 1; // 1-up, 0-down
/*! Led sequence
*
* The sequnce position is indicated by the led that is turned off.
*\n Note that step mutes also leave leds turned off. 
*/
//uint8_t ledSequence[6] = {B01111010, B01111001, B01110011, B01101011, B01011011, B00111011};
uint8_t ledSequence[6] = {0, 1, 3, 4, 5, 6};
/*! @} */


#endif /* GLOBALS_H_ */