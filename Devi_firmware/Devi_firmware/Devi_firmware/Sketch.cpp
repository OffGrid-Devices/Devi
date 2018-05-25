// TODO: [p1nh0] make sin table 14-bit instead of 8-bit?

/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
/*End of auto generated code by Atmel studio */

/*
OffGrid-Devices Devi revB : Arduino+Mozzi based synthesizer
by p1nh0 2018

Mozzi lib by Tim Barrass
Mozzi AUDIO_RATE = 32768Hz
Mozzi mode = HIFI  
Mozzi version = master(22-04-2018)
*/

#include "DeviHardware.h"

#pragma GCC push_options
#pragma GCC optimize (OPTIMIZATION)

#define CONTROL_RATE 512 // must be called above MozziGuts because of my code architecture....
// 512 is optimal for Ead
// 64 is optimal for ADSR

#include <MozziGuts.h>
#include <mozzi_rand.h>
#include <mozzi_fixmath.h>
#include <EEPROM.h>
#include "Button.h"
#include "Potentiometer.h"
#include "Voice.h"
#include "GLOBALS.h"


//Beginning of Auto generated function prototypes by Atmel Studio
void updateControl();
int updateAudio();
// utilities
void setRGB(byte r, byte g, byte b);
void allLedsOff();
// setups
void ledSetup();
void buttonSetup();
void knobSetup();
void voiceSetup();
// controls
void readButtons();
void readKnobs();
void readRotary(); 
// synth functions 
void setMode();
void runMode(); 
void sequencerInterface(); void sequencer(); void incStep();
void trigger(); 
void editor(); 
void save(); // save variables to EEPROM 
void load(); // load variables from EEPROM

//End of Auto generated function prototypes by Atmel Studio



//////////////////////////////////////////////////////////////////////////
// CLASSES //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

// HARDWARE CLASSES
Button button[8];
boolean selectLock = false, modeLock = false;
Potentiometer knob[8];
// SYNTH CLASSES
Voice voice[6];
// PRESET STRUCT
Preset p;



//////////////////////////////////////////////////////////////////////////
// MAIN FUNCTIONS ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void setup(){
	ledSetup();
	buttonSetup();
	knobSetup();
	voiceSetup();
	/*Serial.begin(9600);
	Serial.print("size of struct=");
	Serial.println(sizeof(p));*/
	randSeed();
	startMozzi(CONTROL_RATE);
	setupFastAnalogRead(FASTEST_ADC);
}

void updateControl(){
	readButtons();
	readKnobs();
	readRotary();
	setMode();
	runMode();
}

int updateAudio(){ 
	return ( (long)	voice[0].next() + 
					voice[1].next() + 
					voice[2].next() + 
					voice[3].next() +
					voice[4].next() +
					voice[5].next() 
		   )		>>4; // 6 voices(98304 to 98303) >>4 (-6144 to 6143)
	// 14-bit output: -8192 to 8192
}

void loop(){
  audioHook();
}

//////////////////////////////////////////////////////////////////////////
// SETUP ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void buttonSetup(){
	button[0].init(PINBUT1);
	button[1].init(PINBUT2);
	button[2].init(PINBUT3);
	button[3].init(PINBUT4);
	button[4].init(PINBUT5);
	button[5].init(PINBUT6);
	button[6].init(PINBUT7);
	button[7].init(PINBUT8);	
}
void ledSetup(){
	pinMode(PINRED, OUTPUT);
	pinMode(PINGREEN, OUTPUT);
	pinMode(PINBLUE, OUTPUT);
	pinMode(PINLED1, OUTPUT);
	pinMode(PINLED2, OUTPUT);
	pinMode(PINLED3, OUTPUT);
	pinMode(PINLED4, OUTPUT);
	pinMode(PINLED5, OUTPUT);
	pinMode(PINLED6, OUTPUT);
	pinMode(PINLED7, OUTPUT);
	
	setRGB(LOW, HIGH, LOW); // start with sequencer
}
void knobSetup(){
	knob[0].init(A0);
	knob[1].init(A1);
	knob[2].init(A2);
	knob[3].init(A3);
	knob[4].init(A4);
	knob[5].init(A5);
}
void voiceSetup(){
	for (int i = 0; i < 6; i++)
	{
		voice[i].init(p.pitch[i], CONTROL_RATE);	
	}
}

//////////////////////////////////////////////////////////////////////////
// READ /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void readButtons(){
	button[0].read();
	button[1].read();
	button[2].read();
	button[3].read();
	button[4].read();
	button[5].read();
	button[6].read();
	button[7].read();
	
	//selectLock = false;
	//modeLock = false; 
}
void readKnobs(){
	knob[0].read();
	knob[1].read();
	knob[2].read();
	knob[3].read();
	knob[4].read();
	knob[5].read();
}
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
// MODE /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void setMode(){
	if (button[7].changed && !button[7].state && !modeLock) // trigger on button released
	{
		allLedsOff();
		mode++;
		if(mode>3) mode = 0;
		
		switch(mode){ // 0-Sequencer, 1-Trigger, 2-Edit, 3-Save
			case 0: // Sequencer (green)
				setRGB(LOW, HIGH, LOW);
				break;
			case 1: // Trigger (blue) 
				setRGB(LOW, LOW, HIGH);
				//if(seqTrigger) metro.start();
				break;
			case 2: // Edit (white)
				setRGB(HIGH, HIGH, HIGH);
				break;
			case 3: // Save (red)
				setRGB(HIGH, LOW, LOW);
				break;
			
			default:
			break;
		}
	}
}
void runMode(){
	switch(mode){ // 0-Sequencer, 1-Trigger, 2-Edit, 3-Save
		case 0: // Sequencer (green)
			sequencerInterface();
			sequencer();
			break;
		case 1: // Trigger (blue)
			sequencer();
			//trigger();
			break;
		case 2: // editor (white)
			sequencer();
			//metro.stop();
			break;
		case 3: // save (red)
			sequencer();
			//metro.stop();
			break;
		
		default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// SEQUENCER ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void sequencerInterface(){
	// set mutes and step length 
	if(!button[7].state){
		for(int i = 0; i < 6; i++){
			if (button[i].changed)
			{
				if (button[6].state)
				{
					p.steps = i+1;
					digitalWrite(PINLED2, i>1);
					digitalWrite(PINLED3, i>2);
					digitalWrite(PINLED4, i>3);
					digitalWrite(PINLED5, i>4);
					digitalWrite(PINLED6, i>5);
					selectLock = true;
				}
				else
				{
					if(button[i].state) p.mute[i] = !p.mute[i];
				}
			}
		}
	}
	// set pitch
	if( knob[0].changed ) p.pitch[0] = (knob[0].val >> 1) + 24;
	if( knob[1].changed ) p.pitch[1] = (knob[1].val >> 1) + 24;
	if( knob[2].changed ) p.pitch[2] = (knob[2].val >> 1) + 24;
	if( knob[3].changed ) p.pitch[3] = (knob[3].val >> 1) + 24;	
	if( knob[4].changed ) p.pitch[4] = (knob[4].val >> 1) + 24;	
	
	// set bpm
	if ( button[6].state && knob[5].changed ) // trigger on button pressed
	{
		selectLock = true;
		bpm = (knob[5].val * 2) + 40;
		metro.setBPM( knob[5].val * 8 + 160 ); // 127 * 2(1 for seq 1 for leds) * 16th note(4) + 40bpm (40*4)
	}
	else{
		if( knob[5].changed ) p.pitch[5] = (knob[5].val >> 1) + 24;
	}
	
	// set sequencer start/stop
	if( button[6].changed && !selectLock && !button[6].state) // trigger on button released
	{
		seqOnOff = !seqOnOff;
			
		if ( seqOnOff ) 
		{
			metro.start();
		}
		else 
		{
			metro.stop();
			//allLedsOff();
		}
	}
	
	// set step mode
	if (button[7].state)
	{
		//modeLock = true;
		for (int i = 0; i < 6; i++){
			if (button[i].changed) {
				p.stepMode = i;
				modeLock = true; 
			} 
		}
	}
	else modeLock = false; 
	
	// release select lock
	if(!button[6].state) selectLock = false;
}
void sequencer(){
	// sequencer update
	if ( metro.ready() ){
		
		if ( seqTrigger ) // update sequencer
		{
			for ( int i = 0; i < p.steps; i++ )
			{
				if( p.mute[i] )   digitalWrite(ledPinSequence[i], HIGH);
				else digitalWrite(ledPinSequence[i], LOW);
			}
			//digitalWrite(PINLED1-step, LOW);
			digitalWrite(ledPinSequence[step], LOW);
			digitalWrite(PINLED7, LOW);
			
			voice[step].setPitch( p.pitch[step] );
			
			//if ( mute[step] )   voice[step].noteOff();
			if ( p.mute[step] )   voice[step].startDCA();
			if ( p.steps > 1 ) incStep();
			//if ( mute[step] )   voice[step].noteOn();
		}
		else{ // update leds running a 2x the metronome speed
			digitalWrite(PINLED7, HIGH);
		}
		seqTrigger = !seqTrigger;
	}
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
	switch(p.stepMode){
		case 0: // up
			step++;
			if ( step > p.steps-1)   step = 0;
			break;
		case 1: // down 
			step--;
			if ( step < 0)   step = p.steps-1;
			break;
		case 2: // up&down
			if(stepDir){ // up
				 step++;
				 if ( step > p.steps-1){
					 step = p.steps-2;
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
				if ( step > p.steps-1){
					step = p.steps-1;
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
			step = rand(p.steps);
			break;
		case 5: // random step & pitch
			step = rand(p.steps);
			p.pitch[step] = rand(knob[step].val >> 1) + 24;
			break;
		default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// TRIGGER //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void trigger(){}
	
//////////////////////////////////////////////////////////////////////////
// EDITOR ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void editor(){}
	
//////////////////////////////////////////////////////////////////////////
// SAVE //////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void save(){}
	
//////////////////////////////////////////////////////////////////////////
// LOAD //////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void load(){}


//////////////////////////////////////////////////////////////////////////
// UTILITIES ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void allLedsOff(){
	digitalWrite(PINLED1, LOW);
	digitalWrite(PINLED2, LOW);
	digitalWrite(PINLED3, LOW);
	digitalWrite(PINLED4, LOW);
	digitalWrite(PINLED5, LOW);
	digitalWrite(PINLED6, LOW);
	digitalWrite(PINLED7, LOW);
}
void setRGB(byte r, byte g, byte b){
	digitalWrite(PINRED, r);
	digitalWrite(PINGREEN, g);
	digitalWrite(PINBLUE, b);
}




#pragma GCC pop_options
