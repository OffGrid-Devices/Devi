/*!
* \mainpage Devi firmware code.
* \content Devi is a Phase modulation synth using Arduino and Mozzi library. This code uses Arduino "1.6.5" and Mozzi "v1.0.3rc6". The firmware was developed using "Atmel Studio 7.0.1645".
*/

/*! 
* \file Sketch.cpp
* \brief Devi-Lite firmware.
* Sketch.cpp is the main file. 
*
* \version 1.0
* \date 23/05/2018 03:54
* \author Tiago Angelo (OffGrid-Devices) 
*/ 


/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

#pragma GCC push_options
#pragma GCC optimize (OPTIMIZATION)

#include <MozziGuts.h> // at the top of your sketch
#include "DeviHardware.h"
#include "Globals.h"

//Beginning of Auto generated function prototypes by Atmel Studio

//! Mozzi control update. Where all hardware controls are read and synth parameters are updated
void updateControl();
//! Mozzi audio update. Where all audio calculations are processed. 
int updateAudio();
//! Update button values at CONTROL_RATE
void updateButtons();
//! Update potentiometer values at CONTROL_RATE
void updateKnobs();
//! Update rotary switch values at CONTROL_RATE
void updateRotary();

//End of Auto generated function prototypes by Atmel Studio


void setup() {
	startMozzi(CONTROL_RATE);
	//Serial.begin(9600);
	DDRA = B00000000; // Set all button pins as inputs 
}


void updateControl() {
	buttons = PINA; // Update buttons 
}

int updateAudio() {
	return 0;
}

void loop() {
	audioHook();
}

#pragma GCC pop_options
