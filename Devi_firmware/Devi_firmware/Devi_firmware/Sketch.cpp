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

#define CONTROL_RATE 64 // must be called above MozziGuts because of my code architecture....
// 512 is optimal for Ead
// 64 is optimal for ADSR
// 256 is a nice value
#include <EEPROM.h>
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();
#include <MozziGuts.h>
#include <mozzi_rand.h>
#include <mozzi_fixmath.h>
#include <ADSR.h>
#include "GLOBALS.h"
#include "Voice.h"

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
Voice voice;
ADSR <CONTROL_RATE, AUDIO_RATE> envelope;
uint16_t attack = 100, decay = 100, release = 3000;  
uint8_t sustain	= 255; // (aka decay level)
uint8_t atklevel = 255;
uint16_t sustime = 65535;
//////////////////////////////////////////////////////////////////////////
// MAIN FUNCTIONS ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void HandleNoteOn(byte channel, byte note, byte velocity){
	envelope.noteOn();
}
void HandleNoteOff(byte channel, byte note, byte velocity){
	envelope.noteOff();
}

void setup(){
	MIDI.setHandleNoteOn(HandleNoteOn); 
	MIDI.setHandleNoteOff(HandleNoteOff);
	MIDI.begin(MIDI_CHANNEL_OMNI);  
	
	voice.init(60, CONTROL_RATE);
	envelope.setADLevels(255, sustain);
	envelope.setTimes(attack, decay, sustime, release);
	//envelope.setADLevels(255,64);
	//envelope.setTimes(50,200,10000,200); // 10000 is so the note will sustain 10 seconds unless a noteOff comes

	startMozzi(CONTROL_RATE);
	setupFastAnalogRead(FASTEST_ADC);
}

void updateControl(){
	MIDI.read();
	
	readRotary();
	envelope.update();
	voice.setFreq(1, mozziAnalogRead(A0) + 30);
	voice.setFreq(2, mozziAnalogRead(A1) + 30);
	voice.setFreq(3, mozziAnalogRead(A2) + 30);
	voice.setFreq(4, mozziAnalogRead(A3) + 30);
}

int updateAudio(){ 
	return  (voice.next(rotary) * envelope.next())>>2;
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
