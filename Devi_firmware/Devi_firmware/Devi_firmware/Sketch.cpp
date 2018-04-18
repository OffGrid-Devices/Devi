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
//End of Auto generated function prototypes by Atmel Studio
#define CONTROL_RATE 1024
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> carrier1(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> carrier2(SIN2048_DATA);
/*Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> carrier3(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> carrier4(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> carrier5(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> carrier6(SIN2048_DATA);*/

//ADSR <CONTROL_RATE, AUDIO_RATE> amp;
Ead dca(CONTROL_RATE); 
int gain;
unsigned int att=25, dcy=450;
uint8_t pitch[6] = {36, 39, 43, 46, 48, 29};
uint8_t step = 0; 
Metronome sequencer(500); // 120bpm


uint8_t filter_mode; // 0-LP, 1-BAND, 1-HP
uint8_t fx_mode; // 0-OFF, 1-<<, 2->>, 3-&, 4-|, 5-^
uint8_t exec_mode = 7; // 0-ExtSeq, 1-IntSeq, 2-RndSeq, 3-Stack, 4-Arp, 5-Play, 6-Rnd, 7-Sys 

boolean modebut, _modebut = true; // current and prev. MODE button value

void setup(){
    // set pins
    pinMode(PINRED, OUTPUT);
    pinMode(PINGREEN, OUTPUT);
    pinMode(PINBLUE, OUTPUT);
    pinMode(PINBUT7, INPUT);

	startMozzi(CONTROL_RATE);
	setupFastAnalogRead(FASTEST_ADC);
	//loadPreset(0);
    
	// 
	sequencer.start();
	carrier2.setFreq(220);	
}

void updateControl(){
	// update synth parameters
	
	// read controls
	readPots();
	// set led's 
	setMode();
	
	// sequencer
	if(sequencer.ready()){
		for(int i = PINLED1; i < 11; i++){
			digitalWrite(i, HIGH);
		}
		digitalWrite(PINLED6-step, LOW);
		carrier1.setFreq(mtof(pitch[step]));
		step++;
		if(step > 5) step = 0;
		dca.start(att, dcy);
	}
	gain = (int) dca.next();
}


int updateAudio(){ // TODO: [p1nh0] make sin table 14-bit instead of 8-bit?
	// modulator-->carrier->fx->filter->adsr
	int sig = (carrier1.next() + carrier2.next())>>2;  
	return (sig*gain) >>3; // 14-bit (-8192..8191? or -16384..16833)
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
		exec_mode++;
		if(exec_mode>7) exec_mode = 0;
	
		switch(exec_mode){ // 1-IntSeq, 2-RndSeq, 3-Stack, 4-Arp, 5-Play, 6-Rnd, 7-Sys
			case 0: // external sequencer (red)
			setRGB(HIGH, LOW, LOW);
			break;
			case 1: // internal sequencer (orange)
			setRGB(HIGH, HIGH, LOW);
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