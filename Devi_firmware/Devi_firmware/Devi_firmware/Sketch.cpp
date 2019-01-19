// TODO: make sin table 14-bit instead of 8-bit?

/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
/*End of auto generated code by Atmel studio */

/*
OffGrid-Devices Devi revB : Arduino+Mozzi based synthesizer
firmware version 0.1
by OffGrid-Devices (Tiago Angelo 2018)

Mozzi lib by Tim Barrass
Mozzi AUDIO_RATE = 32768Hz
Mozzi mode = HIFI  
Mozzi version = master(22-04-2018)
*/

#include "DeviHardware.h"

#pragma GCC push_options
#pragma GCC optimize (OPTIMIZATION)

#define CONTROL_RATE 32 // must be called above MozziGuts because of my code architecture....
// 512 is optimal for Ead
// 64 is optimal for ADSR
// 256 is a nice value
#include <EEPROM.h>
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();
#include <MozziGuts.h>
#include <mozzi_rand.h>
#include <mozzi_fixmath.h>
#include <mozzi_midi.h>
#include <ADSR.h>
#include "GLOBALS.h"
#include "Voice.h"
/*#include <Oscil.h>
#include "tables/sin2048_int8.h"*/



//Beginning of Auto generated function prototypes by Atmel Studio
void updateControl();
int updateAudio();
void HandleNoteOn(byte channel, byte note, byte velocity);
void HandleNoteOff(byte channel, byte note, byte velocity);

void readRotary();
//End of Auto generated function prototypes by Atmel Studio



//////////////////////////////////////////////////////////////////////////
// CLASSES //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
Voice voice[NUMVOICES];
uint8_t valloc[NUMVOICES];
/*Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> osc[NUMVOICES];
ADSR <CONTROL_RATE, AUDIO_RATE> env[NUMVOICES];
uint8_t voice[NUMVOICES];*/

/*uint16_t attack = 100, decay = 100, release = 3000;  
uint8_t sustain	= 255; // (aka decay level)
uint8_t atklevel = 255;
uint16_t sustime = 65535;*/

//////////////////////////////////////////////////////////////////////////
// MAIN FUNCTIONS ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void HandleNoteOn(byte channel, byte note, byte velocity){
	  //digitalWrite(PINLED7, HIGH);
	  for (unsigned int i = 0; i < NUMVOICES; i++){
		  if(valloc[i]==0){
			valloc[i] = note;
			voice[i].setPitch(note);
			voice[i].noteOn();
			break;
		  }
	  }
	  
}
void HandleNoteOff(byte channel, byte note, byte velocity){
	//digitalWrite(PINLED7, LOW);
	for (unsigned int i = 0; i < NUMVOICES; i++){
		if(valloc[i]==note){
			valloc[i] = 0;
			voice[i].noteOff();
			break;
		}
	}
}

void setup(){	
	MIDI.setHandleNoteOn(HandleNoteOn); 
	MIDI.setHandleNoteOff(HandleNoteOff);
	MIDI.begin(MIDI_CHANNEL_OMNI);	
	
	for (uint8_t i = 0; i < NUMVOICES; i++)
	{
		voice[i].init(60, CONTROL_RATE);
	}
	
		
	
	startMozzi(CONTROL_RATE);
	setupFastAnalogRead(FASTEST_ADC);
	
	/*for(uint8_t i = 0; i < NUMVOICES; i++){
		osc[i].setTable(SIN2048_DATA);
		env[i].setADLevels(255, sustain);
		env[i].setTimes(attack, decay, sustime, release);
	}*/
}

void updateControl(){
	MIDI.read();
	
	readRotary();
	
	for(uint8_t i = 0; i < NUMVOICES; i++){
		voice[i].updateEnvelope();
	}
}

int updateAudio(){ 
	int sig = 0; 
	for (int i = 0; i < NUMVOICES; i++)
	{
		sig += voice[i].next(rotary)>>1;//>>2;
	}
	return sig >> 1;
	//return voice.next(rotary);
	// 14-bit output: -8192 to 8191
}

void loop(){
  audioHook();
}

//////////////////////////////////////////////////////////////////////////
// SETUP ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// READ /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void readRotary(){
	_rotary = rotary; // set previous values for state change detection
	for(int i = 0; i < 8; i++){
		if( bit_get(PINC, BIT(i)) ) rotary = i; 
	}
	for(int i = 0; i < 4; i++){
		if( bit_get(PIND, BIT(i)) ) rotary = i+8;
	}
}
//////////////////////////////////////////////////////////////////////////
// MIDI /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// MEM ///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// UTILITIES ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

#pragma GCC pop_options
