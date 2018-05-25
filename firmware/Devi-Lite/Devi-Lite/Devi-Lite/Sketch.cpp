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

/*//! Update button values at CONTROL_RATE
void updateButtons();
//! Update potentiometer values at CONTROL_RATE
void updateKnobs();
//! Update rotary switch values at CONTROL_RATE
void updateRotary();
*/

/*! Updates parameters according to mode. 
*
* This is the main function that selects which mode to run (sequencer, trigger, edit or save)
*/
void runMode(); 
//! Sequencer function, updated in runMode() according to "mode" variable.
void sequencer();
//! Trigger function, updated in runMode() according to "mode" variable.
void trigger();
//! Edit function, updated in runMode() according to "mode" variable.
void edit();
//! Save function, updated in runMode() according to "mode" variable.
void save();
//! Load function loads presets using the rotary switch when in sequencer or trigger mode
void load(int preset);


//End of Auto generated function prototypes by Atmel Studio


void setup() {
	Serial.begin(9600);
	startMozzi(CONTROL_RATE); // setup mozzi 
	setupFastAnalogRead(FASTEST_ADC); // use mozzi analogRead

	// Pin Setup (1=output, 0=input)
	DDRH = DDRH & B01111011; // Set leds1~6 as outputs
	DDRB = DDRB & B00010000; // Set Function led as output
	DDRE = DDRE & B00111000; // Set Mode (RGB) led as output
	PORTE |= modeColors[mode]; // Light Mode led at startup
	//sbi(PORTE, 3);
	DDRA = B00000000; // Set all button pins as inputs
	DDRC = B00000000; // Set rotary switch 1~8 pins as inputs 
	DDRD = DDRD & B00001111; // Set rotary switch 9~12 pins as inputs (without changing the remaining pins on the same port)
}


void updateControl() {
	// READ UI HARDWARE
	// Update Buttons
	_buttons = buttons; 
	buttons = PINA;
	// Update RotarySwitch 
	_rotary = rotary; // set previous values for state change detection
	for(int i = 0; i < ROTLOWER; i++){
		if( bit_get(PINC, BIT(i)) ) rotary = i;
	}
	for(int i = 0; i < ROTUPPER; i++){
		if( bit_get(PIND, BIT(i)) ) rotary = i+ROTLOWER;
	}
	// Update Knobs
	for(int i=0; i < NUMVOICES; i++){
		knobs[i] = mozziAnalogRead(i) >> 3 ; // convert from 0..1023 to 0..127
	}
	
	// Update UI Variable: Mode
	if (buttons == B01111111 && buttons != _buttons) {
		mode++; // increment mode
		if(mode>NUMMODES-1) mode = 0; 
		cbi(PORTE, 3); // clear RGB pins
		cbi(PORTE, 4); 
		cbi(PORTE, 5);
		PORTE |= modeColors[mode]; // set RGB color
	}
	
	if(mode < 2 && _rotary != rotary) load(rotary);
	runMode(); // run main functions 
	
}

int updateAudio() {
	return 0;
}

void loop() {
	audioHook();
}



void runMode(){
	switch(mode){
		case 0: 
			sequencer();
			break;
		case 1:	
			trigger();
			break;
		case 2:
			edit();
			break;
		case 3: 
			save();
			break; 
		default:
			break;
	}
}			
	
void sequencer(){}

void trigger(){}

void edit(){}
	
void save(){}

void load(int preset){}




#pragma GCC pop_options
