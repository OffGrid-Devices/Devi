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
#include <Metronome.h> 
#include <mozzi_rand.h>
#include <mozzi_fixmath.h>
#include <IntMap.h>
#include "DeviHardware.h"
#include "Globals.h"
#include "Voice.h"

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
//! Update sequencer parameters only in Sequencer Mode.
void updateSequencer();
//! Run sequence. It can execute in every Mode as long as "seqOnOff" is true.
void runSequencer();
//! Function to increment steps according to step mode
void incStep();
//! Trigger function, updated in runMode() according to "mode" variable.
void trigger();
//! Edit function, updated in runMode() according to "mode" variable.
void edit();
//! Save function, updated in runMode() according to "mode" variable.
void save();
//! Load function loads presets using the rotary switch when in sequencer or trigger mode
void load(int preset);
//! Turn leds1~6 on 
void ledsOn(); 
//! Turn leds1~6 off
void ledsOff();


//End of Auto generated function prototypes by Atmel Studio

// Instantiated objects
Voice voice[NUMVOICES]; 
IntMap mapFilterFreq(0, 255, MINFILTER, MAXFILTER); 

void setup() {
	if(DEBUG) Serial.begin(9600);
	startMozzi(CONTROL_RATE); // setup mozzi 
	setupFastAnalogRead(FASTEST_ADC); // use mozzi analogRead
	
	// Pin Setup (1=output, 0=input)
	//DDRH = DDRH & B01111011; // Set leds1~6 as outputs
	pinMode(17, OUTPUT);
	pinMode(16, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);
	// Set Function led as output (watch out, port manipulation was messing with Mozzi)
	pinMode(10, OUTPUT); 
	// Set Mode (RGB) led as output
	pinMode(5, OUTPUT);
	pinMode(3, OUTPUT);
	digitalWrite(3, HIGH);
	pinMode(2, OUTPUT);
	//DDRE = DDRE & B00111000; 
	//PORTE |= modeColors[mode]; // Light Mode led at startup
	DDRA = B00000000; // Set all button pins as inputs
	DDRC = B00000000; // Set rotary switch 1~8 pins as inputs 
	//DDRD = DDRD & B00001111; // Set rotary switch 9~12 pins as inputs (without changing the remaining pins on the same port)
	pinMode(21, INPUT);
	pinMode(20, INPUT);
	pinMode(19, INPUT);
	pinMode(18, INPUT);
	
	// Synth Setup
	for (int i = 0; i < 6; i++)
	{
		voice[i].init(CONTROL_RATE, MINPITCH); // init oscillator pitches
	}
}


void updateControl() {
	// READ UI HARDWARE
	// Read Buttons
	_buttons = buttons; 
	buttons = PINA;
	modeLock = !bit_get(buttons, BIT(7)); // set Mode lock
	functionLock = !bit_get(buttons, BIT(6)); // set Function lock 
	
	// Read RotarySwitch 
	_rotary = rotary; // set previous values for state change detection
	for(int i = 0; i < ROTLOWER; i++){
		if( bit_get(PINC, BIT(i)) ) rotary = i;
	}
	for(int i = 0; i < ROTUPPER; i++){
		if( bit_get(PIND, BIT(i)) ) rotary = i+ROTLOWER;
	}
	// Read Knobs
	for(int i=0; i < NUMVOICES; i++){
		_knobs[i] = knobs[i]; 
		knobs[i] = mozziAnalogRead(i) >> 2 ; // convert from 0..1023 to 0..255
	}
	//TODO: if(mode < 2 && _rotary != rotary) load(rotary); // load preset
	if (buttons == B11111111 && _buttons == B01111111 && !paramChange) { // if Mode button released
		ledsOff();
		modeLock == false;
		mode++; // increment mode
		if(mode>NUMMODES-1) mode = 0;
		cbi(PORTE, 3); // clear RGB pins
		cbi(PORTE, 4);
		cbi(PORTE, 5);
		PORTE |= modeColors[mode]; // set RGB color
	}
	
	runMode(); // run main functions 
	
	
}

int updateAudio() {
	return ( (long)	voice[0].next() +
	voice[1].next() +
	voice[2].next() +
	voice[3].next() +
	voice[4].next() +
	voice[5].next()
	)		>>4; // 6 voices(98304 to 98303) >>4 (-6144 to 6143)
	// 14-bit output: -8192 to 8192
}

void loop() {
	audioHook();
}

void runMode(){
	switch(mode){
		case 0: 
			updateSequencer();
			runSequencer();
			break;
		case 1:	
			runSequencer();
			trigger();
			break;
		case 2:
			runSequencer();
			edit();
			break;
		case 3: 
			runSequencer();
			save();
			break; 
		default:
			break;
	}
}			
	
//////////////////////////////////////////////////////////////////////////
// UPDATE SEQUENCER PARAMETERS ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void updateSequencer(){
	
	// Sequencer Start/Stop
	if(!functionLock && buttons==B11111111 && _buttons==B10111111){ // start/stop on Function button release
		seqOnOff = !seqOnOff; 
		if(seqOnOff) metro.start(); 
		else metro.stop(); cbi(PORTB, 4);
	}
	
	// Regular controls (no combos)
	if(!modeLock && !functionLock){ 
		for(int i = 0; i < NUMVOICES; i++){
			// Update pitch
			if(knobs[i] != _knobs[i]){
				voice[i].setPitch(knobs[i] >> 2);
			}
		}
		// Update Mutes 
		if(buttons != _buttons){
			stepMutes ^= (255-buttons);
			Serial.println(stepMutes, BIN);
		}
	}
	/*
	// FUNCTION Combos
	if( !bit_get(buttons, 6)){ // while FUNCTION button is pressed
		// knob 1 sets bpm
		if(knobs[0] != _knobs[0]) {
			bpm = knobs[0] + MINBPM;
			metro.setBPM( bpm*subdivisions[subdivision] * 2);
		}
		// knob 2 sets subdivion value
		if(knobs[1] != _knobs[1]) {
			subdivision = knobs[1] >> 5; // from 0..255 to 0..7
			metro.setBPM( bpm*subdivisions[subdivision] * 2);
		}
		//knob 3 sets scale
		if(knobs[2] != _knobs[0]) {
			//TODO: implement scale feature 
		}
		// knob 4 shifts all pitches up or down
		if(knobs[3] != _knobs[3]) {
			uint8_t pitchInc = knobs[3] - _knobs[3];
			for(int i = 0; i < NUMVOICES; i++)
			{
				pitchInc += voice[i].pitch;
				voice[i].setPitch(pitchInc);
			}
		}
		// knob 5 shifts all filter frequencies
		if(knobs[4] != _knobs[4]) {
			uint8_t freqInc = knobs[4] - _knobs[4];
			for(int i = 0; i < NUMVOICES; i++){
				voice[i].filterfreq += mapFilterFreq(freqInc);
			}
		}
		// knob 6 shifts all filter resonances
		if(knobs[5] != _knobs[5]) {
			uint8_t resInc = knobs[5] - _knobs[5];
			for(int i = 0; i < NUMVOICES; i++){
				voice[i].res += resInc;
				//TODO: check if res=0 is glitching...
			}
		}
	}
	*/
	// MODE Combos
	ifif(!bit_get(buttons, BIT(7))){ // while MODE button is pressed // while MODE button is pressed
		paramChange = false; 
		for(int i = 0; i < NUMVOICES; i++){
			if(bit_get(buttons, BIT(i))) stepMode = i; paramChange = true; 
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// RUN SEQUENCER /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void runSequencer(){
	if ( metro.ready() ){
		PORTB ^= BIT(4); // toggle PINLED7
		if ( seqTrigger ) // update sequencer
		{
			// Led Sequence
			if(mode < 1){ // Run leds1~6 only on Sequencer Mode
			   // light up all leds
			   ledsOn();
			   // turn off leds if muted
			   for(int i = 0; i < NUMVOICES; i++){
				   if( bit_get(stepMutes, BIT(i)) ) cbi(PORTH, ledSequence[i]);
			   }
			   // turn off led on current step 
			   cbi(PORTH, ledSequence[step]);
			   
			   //TODO: since PH2 is not connected to any led and stepMutes has sequential bytes from 0 to 5 how to do this with bit manipulation ? 
			   /*PORTH |= B01111011;// turn all leds on 
			   uint8_t leds = (stepMutes << 6);
			   leds = leds >> 6; // get first two bits
			   uint8_t upperBits = stepMutes >> 2; 
			   upperBits = upperBits << 3; // get bits 3, 4, 5 and 6 and shitft left one place
			   leds |= upperBits; 
			   leds |= ledSequence[step];
			   PORTH = leds;*/
			}
			// Trigger Envelopes 
			if(!bit_get(stepMutes, BIT(step))) voice[step].startDCA();
			// Increment Step
			if ( steps > 1 ) incStep();
		}
		seqTrigger = !seqTrigger;
	}
	// Update Envelopes
	voice[0].updateEnvelopes();
	voice[1].updateEnvelopes();
	voice[2].updateEnvelopes();
	voice[3].updateEnvelopes();
	voice[4].updateEnvelopes();
	voice[5].updateEnvelopes();
	// ADSR
	/*voice[0].updateEnv();
	voice[1].updateEnv();
	voice[2].updateEnv();
	voice[3].updateEnv();
	voice[4].updateEnv();
	voice[5].updateEnv();*/
}

void incStep(){
	switch(stepMode){
		case 0: // up
		step++;
		if ( step > steps-1)   step = 0;
		break;
		case 1: // down
		step--;
		if ( step < 0)   step = steps-1;
		break;
		case 2: // up&down
		if(stepDir){ // up
			step++;
			if ( step > steps-1){
				step = steps-2;
				stepDir = 0;
			}
		}
		else { // down
			step--;
			if ( step < 0){
				step = 1;
				stepDir = 1;
			}
		}
		break;
		case 3: // palindrome
		if(stepDir){ // up
			step++;
			if ( step > steps-1){
				step = steps-1;
				stepDir = 0;
			}
		}
		else { // down
			step--;
			if ( step < 0){
				step = 0;
				stepDir = 1;
			}
		}
		break;
		case 4: // random step
			step = rand(steps);
		break;
			case 5: // random step & pitch
			step = rand(steps);
			voice[step].setPitch(rand(knobs[step] >> 2));
		break;
		default:
		break;
	}
}


void trigger(){}


void edit(){}

	
void save(){}


void load(int preset){}

void ledsOn(){
	sbi(PORTH, 0); // PH0
	sbi(PORTH, 1); // PH1
	sbi(PORTH, 3); // PH3
	sbi(PORTH, 4); // PH4
	sbi(PORTH, 5); // PH5
	sbi(PORTH, 6); // PH6
}

void ledsOff(){
	cbi(PORTH, 0); // PH0
	cbi(PORTH, 1); // PH1
	cbi(PORTH, 3); // PH3
	cbi(PORTH, 4); // PH4
	cbi(PORTH, 5); // PH5
	cbi(PORTH, 6); // PH6
}

#pragma GCC pop_options
