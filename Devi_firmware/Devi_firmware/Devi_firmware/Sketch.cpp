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
#include <Ead.h> // exponential attack decay //#include <ADSR.h>
#include <Metronome.h>
#include <mozzi_midi.h>

#include "GLOBALS.h"
#include "Button.h"
#include "Sequencer.h"

#include "tables/sin2048_int8.h"

//Beginning of Auto generated function prototypes by Atmel Studio
//void setFreqs(Q8n8 midi_note);
void updateControl();
int updateAudio();
void savePreset(int p);
void loadPreset(int p);
void execSequencer();
void execPlay(); 
void execEdit();
void readControls();
void setLeds(); // ?? 
void setRGB(byte r, byte g, byte b);
void setMode();
void readPots();
void readButtons();
void allLedsOff();
//End of Auto generated function prototypes by Atmel Studio
#define CONTROL_RATE 512
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> carrier1(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> carrier2(SIN2048_DATA);
/*Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> carrier3(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> carrier4(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> carrier5(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> carrier6(SIN2048_DATA);*/

//ADSR <CONTROL_RATE, AUDIO_RATE> amp;
// SYNTH VARIABLES
Ead dca(CONTROL_RATE); 
int gain;
unsigned int att=25, dcy=450;
uint8_t pitch[6] = {36, 39, 43, 46, 48, 29};
boolean mute[6] = {true, true, true, true, true, true};
uint8_t step = 0;
uint16_t bpm = 4*120; 
//const uint8_t blinkRatio = bpm/2; 
boolean seqTrigger = 1; // actually runs at twice the audible sequencer rate to turn bpm led indicator on/off (1-triggers envelopes and led on; 0- triggers led off)
Metronome sequencer(60000/bpm/2); // 120bpm
boolean seqSwitch = true;

uint8_t filter_mode; // 0-LP, 1-BAND, 1-HP
uint8_t fx_mode; // 0-OFF, 1-<<, 2->>, 3-&, 4-|, 5-^
uint8_t exec_mode = 7; // 0-ExtSeq, 1-IntSeq, 2-RndSeq, 3-Stack, 4-Arp, 5-Play, 6-Rnd, 7-Sys 

// HARDWARE VARIABLES
boolean modebut, _modebut = true; // current and prev. MODE button value
Button button[8]; 

void setup(){
    // set pins
	// LED's 
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

    pinMode(PINBUT7, INPUT);
	button[0].init(PINBUT1);
	button[1].init(PINBUT2);
	button[2].init(PINBUT3);
	button[3].init(PINBUT4);
	button[4].init(PINBUT5);
	button[5].init(PINBUT6);
	button[7].init(PINBUT8);
	
	//Serial.begin(9600);
	startMozzi(CONTROL_RATE);
	setupFastAnalogRead(FASTEST_ADC);
	//sequencer.setBPM(bpm*2.f);
	//loadPreset(0);
    
	// 
	sequencer.stop();
	carrier2.setFreq(220);	
}

void updateControl(){
	// update synth parameters
	
	// read controls
	readPots();
	readButtons();
	// set led's 
	setMode();
	
	// sequencer
	if ( sequencer.ready() ){
			
			if ( seqTrigger )
			{ // trigger on
				for ( int i = 0; i < 6; i++ )
				{
					if( mute[i] )   digitalWrite(PINLED1-i, HIGH);
					else digitalWrite(PINLED1-i, LOW);
				}
				digitalWrite(PINLED1-step, LOW);
				digitalWrite(PINLED7, HIGH);
				carrier1.setFreq( mtof(pitch[step]) );
				if ( mute[step] )   dca.start(att, dcy);
				step++;
				if ( step > 5 )   step = 0;
			}
			else{ // trigger off
				digitalWrite(PINLED7, LOW); 
			}
			seqTrigger = !seqTrigger;
	}
	
	gain = (int) dca.next();
}


int updateAudio(){ // TODO: [p1nh0] make sin table 14-bit instead of 8-bit?
	// modulator-->carrier->fx->filter->adsr
	int sig = (carrier1.next() + carrier2.next())>>2;  
	return (sig*gain)>>1; // 14-bit (-8192..8191? or -16384..16833)
	// scale from 8-bit to 14-bit
	// gain -128..127, carrier -128..127
}

void loop(){
  audioHook();
}

void setRGB(byte r, byte g, byte b){
	digitalWrite(PINRED, r);
	digitalWrite(PINGREEN, g);
	digitalWrite(PINBLUE, b);
}

void setMode(){
	modebut = digitalRead(PINBUT7); // read MODE button
	if (modebut < _modebut){
		allLedsOff();
		exec_mode++;
		if(exec_mode>7) exec_mode = 0;
	
		switch(exec_mode){ // 1-IntSeq, 2-RndSeq, 3-Stack, 4-Arp, 5-Play, 6-Rnd, 7-Sys
			case 0: // external sequencer (red)
			setRGB(HIGH, LOW, LOW);
			break;
			case 1: // internal sequencer (orange)
			setRGB(HIGH, HIGH, LOW);
			if(seqTrigger) sequencer.start();
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
	_modebut = modebut;
}

void readPots(){
	for (int i = 0; i < 6; i++)
	{
		pitch[i] = (mozziAnalogRead(i)>>4)+24; // notes from 24..88 
	}
}

void readButtons(){
	if( button[0].changed() )	mute[0] = !mute[0];
	if( button[1].changed() )	mute[1] = !mute[1];
	if( button[2].changed() )	mute[2] = !mute[2];
	if( button[3].changed() )	mute[3] = !mute[3];
	if( button[4].changed() )	mute[4] = !mute[4];
	if( button[5].changed() )	mute[5] = !mute[5];
	
	if ( exec_mode == 1)
	{
		if( button[7].changed() )
		{
			seqSwitch = !seqSwitch;
			if ( seqSwitch ) sequencer.start();
			else {
				sequencer.stop();
				allLedsOff();
			}
		}
	}
	else
	{
		sequencer.stop();	
	}
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