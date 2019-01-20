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

#define CONTROL_RATE 128 // must be called above MozziGuts because of my code architecture....
// 512 is optimal for Ead
// 64 is optimal for ADSR
#include <EEPROM.h>
#include <MIDI.h>
#include <MozziGuts.h>
#include <mozzi_rand.h>
#include <mozzi_fixmath.h>
#include <mozzi_midi.h>
#include <Oscil.h>
#include "tables/sin2048_int8.h"*/
#include "GLOBALS.h"
#include "Voice.h"

//Beginning of Auto generated function prototypes by Atmel Studio
void updateControl();
int  updateAudio();
void HandleNoteOn(byte channel, byte note, byte velocity);
void HandleNoteOff(byte channel, byte note, byte velocity);

void readRotary();
//End of Auto generated function prototypes by Atmel Studio

//////////////////////////////////////////////////////////////////////////
// OBJECTS //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> osc[NUMVOICES];
Voice voice[NUMVOICES];
Q8n0 valloc[NUMVOICES];
Q8n0 depth[NUMVOICES];
Q8n0 vnote[NUMVOICES];
float detune[NUMVOICES];
Q7n0 coarse[NUMVOICES];

//////////////////////////////////////////////////////////////////////////
// MIDI /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void HandleNoteOn(byte channel, byte note, byte velocity){
	  for (uint8_t i = 0; i < NUMVOICES; i++){
		  if(valloc[i]==0){
			valloc[i] = note;
			vnote[i] = note;
			voice[i].noteOn();
			break;
		  }
	  }
}
void HandleNoteOff(byte channel, byte note, byte velocity){
	for (uint8_t i = 0; i < NUMVOICES; i++){
		if(valloc[i]==note){
			valloc[i] = 0;
			voice[i].noteOff();
			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// MAIN FUNCTIONS ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
MIDI_CREATE_DEFAULT_INSTANCE();
void setup(){		
	MIDI.setHandleNoteOn(HandleNoteOn); 
	MIDI.setHandleNoteOff(HandleNoteOff);
	MIDI.begin(MIDI_CHANNEL_OMNI);	
	for (uint8_t i = 0; i < NUMVOICES; i++)
	{
		osc[i].setTable(SIN2048_DATA);
		voice[i].init(CONTROL_RATE);
		depth[i] = 255;
	}
	
	startMozzi(CONTROL_RATE);
	setupFastAnalogRead(FASTEST_ADC);
}

//////////////////////////////////////////////////////////////////////////
// CONTROL///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void updateControl(){
	MIDI.read();
	readRotary();
	for(uint8_t i = 0; i < NUMVOICES; i++){
		// envelope update
		voice[i].updateEnvelope(depth[i]);
		// oscillator update
		coarse[i] = coarseTable[mozziAnalogRead(A4)>>7];
		//detune[i] = mozziAnalogRead(A5)/1024.f -0.5f;
		detune[i] = detuneTable[mozziAnalogRead(A5)>>3];
		Q16n16 notein = float_to_Q16n16(detune[i] + coarse[i] + vnote[i] );
		osc[i].setFreq_Q16n16( Q16n16_mtof(notein)); 
	}
}

//////////////////////////////////////////////////////////////////////////
// AUDIO ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
int updateAudio(){ 
	int sig = 0; 
	for (int i = 0; i < NUMVOICES; i++)
	{
		sig += (voice[i].next() * osc[i].next() )>>6; //ensure output: -4096 to 4095
	}
	return sig;
	//return voice.next(rotary);
	// 14-bit output: -8192 to 8191
}
void loop(){ audioHook(); }

//////////////////////////////////////////////////////////////////////////
// SETUP FUNCTIONS //////////////////////////////////////////////////////
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
// MEM ///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// UTILITIES ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

#pragma GCC pop_options
