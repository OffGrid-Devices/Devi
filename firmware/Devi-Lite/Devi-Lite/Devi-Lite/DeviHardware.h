/*!
* \file DeviHardware.h
* \brief Hardware description.
* This file contains hardware pin mappings used in the Devi synthesiser.
*
* \version 1.0
* \date 23/05/2018 03:54
* \author Tiago Angelo (OffGrid-Devices)
*/


#ifndef DEVIHARDWARE_H_
#define DEVIHARDWARE_H_

//COMPILER
//#define OPTIMIZATION "O3"

/*! \defgroup Buttons
* Buttons are mapped to pins on PORT A.
*  @{
*/
//! Button 1 (PA0)
#define PINBUT1 22
//! Button 2 (PA1)
#define PINBUT2 23
//! Button 3 (PA2)
#define PINBUT3 24
//! Button 4 (PA3)
#define PINBUT4 25
//! Button 5 (PA4)
#define PINBUT5 26
//! Button 6 (PA5)
#define PINBUT6 27
//! Function button (PA6)
#define PINBUT7 28
//! Mode button (PA7)
#define PINBUT8 29
/*! @} */

/*! \defgroup Potentiometers
* Potentiometers are mapped to pins on PORT F (analog input).
*  @{
*/
//! Knob 1 (PF0)
#define PINPOT1 A0
//! Knob 1 (PF0)
#define PINPOT2 A1
//! Knob 1 (PF0)
#define PINPOT3 A2
//! Knob 1 (PF0)
#define PINPOT4 A3 
//! Knob 1 (PF0)
#define PINPOT5 A4 
//! Knob 1 (PF0)
#define PINPOT6 A5
/*! @} */
 

/*! \defgroup LEDs
* Voice/step LEDs are mapped to pins on PORT H, while "Function" LED is mapped to PORT B and "Mode" LED is mapped to PORT E. 
*  @{
*/
//! LED 1 (PH0)
#define PINLED1 17
//! LED 2 (PH1)
#define PINLED2 16
//! LED 3 (PH2)
#define PINLED3 6
//! LED 4 (PH3) 
#define PINLED4 7
//! LED 5 (PH4) 
#define PINLED5 8
//! LED 6 (PH5) 
#define PINLED6 9 
//! Function LED (PB4)
#define PINLED7 10
// Mode RGB LED - red (PE3)
#define PINRED 5 
// Mode RGB LED - green (PE3)
#define PINGREEN 3
// Mode RGB LED - blue (PE3)
#define PINBLUE 2 
/*! @} */

/*! \defgroup RotarySwitch 
* 12-step rotary switch mapped to pin on PORT C and D.
*  @{
*/
//! Position 1 (PC0)
#define PINROT1 37
//! Position 2 (PC1)
#define PINROT2 36
//! Position 3 (PC2)
#define PINROT3 35 
//! Position 4 (PC3)
#define PINROT4 34 
//! Position 5 (PC4)
#define PINROT5 33 
//! Position 6 (PC5)
#define PINROT6 32 
//! Position 7 (PC6)
#define PINROT7 31 
//! Position 8 (PC7)
#define PINROT8 30 
//! Position 9 (PD0)
#define PINROT9 21 
//! Position 10 (PD1)
#define PINROT10 20
//! Position 11 (PD2)
#define PINROT11 19
//! Position 12 (PD3)
#define PINROT12 18
/*! @} */


#endif /* DEVIHARDWARE_H_ */