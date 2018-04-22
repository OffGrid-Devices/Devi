// TODO: [p1nh0] make sin table 14-bit instead of 8-bit?

/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
/*End of auto generated code by Atmel studio */

/*
OffGrid-Devices Devi revB : Arduino+Mozzi based synthesizer
by p1nh0 2018

Mozzi AUDIO_RATE = 32768
Mozzi mode = HIFI  
*/

#include <MozziGuts.h>
#include <Oscil.h>
#include <Ead.h>
#include <Metronome.h>
#include <mozzi_midi.h>
#include <mozzi_rand.h>

#include "GLOBALS.h"

#include "Button.h"
#include "Potentiometer.h"

#include "tables/sin2048_int8.h"

//Beginning of Auto generated function prototypes by Atmel Studio
void updateControl();
int updateAudio();

void buttonSetup();
void ledSetup();
void knobSetup();

void setRGB(byte r, byte g, byte b);
void allLedsOff();

void readButtons();
void readKnobs();
void setMode();
void execMode(); 
void execMode0(); void execMode1(); void execMode2(); void execMode3(); 
void execMode4(); void execMode5(); void execMode6(); void execMode7();

void incStep();
//End of Auto generated function prototypes by Atmel Studio

#define CONTROL_RATE 512

Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> carrier1(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> carrier2(SIN2048_DATA);

// SYNTH VARIABLES
Ead dca(CONTROL_RATE); 
int gain;
unsigned int att=25, dcy=450;
uint8_t pitch[6] = {36, 39, 43, 46, 48, 29};

boolean mute[6] = {true, true, true, true, true, true};
int8_t step = 0, steps = 6;
uint16_t bpm = 4*120, _bpm = bpm; 
boolean seqTrigger = 1; // actually runs at twice the audible sequencer rate to turn bpm led indicator on/off (1-triggers envelopes and led on; 0- triggers led off)
Metronome metro(60000/bpm/2); // 120bpm
boolean seqSwitch = true;
uint8_t stepMode = 0; // up, down, up&down, palindrome, random step, random step & pitch
boolean stepDir = 1; // 1-up, 0-down

uint8_t filter_mode; // 0-LP, 1-BAND, 1-HP
uint8_t fx_mode; // 0-OFF, 1-<<, 2->>, 3-&, 4-|, 5-^
uint8_t exec_mode = 7; // 0-ExtSeq, 1-IntSeq, 2-RndSeq, 3-Stack, 4-Arp, 5-Play, 6-Rnd, 7-Sys 

// HARDWARE VARIABLES
Button button[8];
boolean selectLock = false, modeLock = false;
Potentiometer knob[8];

void setup(){
	ledSetup();
	buttonSetup();
	knobSetup();
	//Serial.begin(9600);
	randSeed();
	startMozzi(CONTROL_RATE);
	setupFastAnalogRead(FASTEST_ADC);

	carrier2.setFreq(220);	
}

void updateControl(){
	readButtons();
	readKnobs();
	setMode();
	execMode();
}


int updateAudio(){ 
	int sig = (carrier1.next() + carrier2.next())>>2;  
	return (sig*gain)>>1; // 14-bit (-8192..8191? or -16384..16833)
	// scale from 8-bit to 14-bit (gain{-128, 127}, oscillator {-128, 127})
}

void loop(){
  audioHook();
}

// DEVI FUNCTIONS
void buttonSetup(){
	button[0].init(PINBUT1);
	button[1].init(PINBUT2);
	button[2].init(PINBUT3);
	button[3].init(PINBUT4);
	button[4].init(PINBUT5);
	button[5].init(PINBUT6);
	button[6].init(PINBUT8);
	button[7].init(PINBUT7);	
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
}
void knobSetup(){
	knob[0].init(A0);
	knob[1].init(A1);
	knob[2].init(A2);
	knob[3].init(A3);
	knob[4].init(A4);
	knob[5].init(A5);
}

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

void setMode(){
	if (button[7].changed && !button[7].state && !modeLock) // trigger on button released
	{
		allLedsOff();
		exec_mode++;
		if(exec_mode>7) exec_mode = 0;
		
		switch(exec_mode){ // 1-IntSeq, 2-RndSeq, 3-Stack, 4-Arp, 5-Play, 6-Rnd, 7-Sys
			case 0: // external sequencer (red)
			setRGB(HIGH, LOW, LOW);
			break;
			case 1: // internal sequencer (orange)
			setRGB(HIGH, HIGH, LOW);
			if(seqTrigger) metro.start();
			break;
			case 2: // randomize sequence (purple)
			setRGB(HIGH, LOW, HIGH);
			break;
			case 3: // external play stack notes (green)
			setRGB(LOW, HIGH, LOW);
			break;
			case 4: // external play arpeggio (cian)
			setRGB(LOW, HIGH, HIGH);
			break;
			case 5: // internal play (blue)
			setRGB(LOW, LOW, HIGH);
			break;
			case 6: // randomize synth (white)
			setRGB(HIGH, HIGH, HIGH);
			break;
			case 7: // system (off)
			setRGB(LOW, LOW, LOW);
			break;
			
			default:
			break;
		}
	}
}
void execMode(){
	switch(exec_mode){ // 1-IntSeq, 2-RndSeq, 3-Stack, 4-Arp, 5-Play, 6-Rnd, 7-Sys
		case 0: // external sequencer (red)
		metro.stop();
		break;
		case 1: // internal sequencer (orange)
		execMode1();
		break;
		
		case 2: // randomize sequence (purple)
		metro.stop();
		break;
		case 3: // external play stack notes (green)
		metro.stop();
		break;
		case 4: // external play arpeggio (cian)
		metro.stop();
		break;
		case 5: // internal play (blue)
		metro.stop();
		break;
		case 6: // randomize synth (white)
		metro.stop();
		break;
		case 7: // system (off)
		metro.stop();
		break;
		
		default:
		break;
	}
}

void execMode1(){
	// set mutes and step length 
	if(!button[7].state){
		for(int i = 0; i < 6; i++){
			if (button[i].changed)
			{
				if (button[6].state)
				{
					steps = i+1;
					digitalWrite(PINLED2, i>1);
					digitalWrite(PINLED3, i>2);
					digitalWrite(PINLED4, i>3);
					digitalWrite(PINLED5, i>4);
					digitalWrite(PINLED6, i>5);
					selectLock = true;
				}
				else
				{
					if(button[i].state) mute[i] = !mute[i];
				}
			}
		}
	}
	// set pitch
	if( knob[0].changed ) pitch[0] = (knob[0].val >> 1) + 24;
	if( knob[1].changed ) pitch[1] = (knob[1].val >> 1) + 24;
	if( knob[2].changed ) pitch[2] = (knob[2].val >> 1) + 24;
	if( knob[3].changed ) pitch[3] = (knob[3].val >> 1) + 24;	
	if( knob[4].changed ) pitch[4] = (knob[4].val >> 1) + 24;	
	
	// set bpm
	if ( button[6].state && knob[5].changed ) // trigger on button pressed
	{
		selectLock = true;
		bpm = (knob[5].val * 2) + 40;
		metro.setBPM( knob[5].val * 8 + 160 ); // 127 * 2(1 for seq 1 for leds) * 16th note(4) + 40bpm (40*4)
	}
	else{
		if( knob[5].changed ) pitch[5] = (knob[5].val >> 1) + 24;
	}
	
	// set sequencer start/stop
	if( button[6].changed && !selectLock && !button[6].state) // trigger on button released
	{
		seqSwitch = !seqSwitch;
			
		if ( seqSwitch ) 
		{
			metro.start();
		}
		else 
		{
			metro.stop();
			allLedsOff();
		}
	}
	
	// set step mode
	if (button[7].state)
	{
		//modeLock = true;
		for (int i = 0; i < 6; i++){
			if (button[i].changed) {
				stepMode = i;
				modeLock = true; 
			} 
		}
	}
	else modeLock = false; 
	
	// release select lock
	if(!button[6].state) selectLock = false;
		
	// sequencer update
	if ( metro.ready() ){
		
		if ( seqTrigger ) // update sequencer
		{
			for ( int i = 0; i < steps; i++ )
			{
				if( mute[i] )   digitalWrite(PINLED1-i, HIGH);
				else digitalWrite(PINLED1-i, LOW);
			}
			digitalWrite(PINLED1-step, LOW);
			digitalWrite(PINLED7, HIGH);
			carrier1.setFreq( mtof(pitch[step]) );
			if ( mute[step] )   dca.start(att, dcy);
			if ( steps > 1 ) incStep();
		}
		else{ // update leds running a 2x the metronome speed
			digitalWrite(PINLED7, LOW);
		}
		seqTrigger = !seqTrigger;
	}
	
	gain = (int) dca.next();
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
			pitch[step] = rand(knob[step].val >> 1) + 24;
			break;
		default:
		break;
	}
}
