/*
* Voice.cpp
*
* Created: 22-04-2018 19:25:00
* Author: tiago
*/


#include "Voice.h"

#pragma GCC push_options
#pragma GCC optimize (OPTIMIZATION)

// default constructor
Voice::Voice()
{
	
} //Voice

// default destructor
Voice::~Voice()
{
} //~Voice

void Voice::init(uint8_t note, uint16_t ctrl_rate){
	carrier.setTable(SIN2048_DATA);
	carrier.setFreq( mtof(note) );
	modulator.setTable(SIN2048_DATA);
	modulator.setFreq( mtof(note) );
	dca = new Ead(ctrl_rate);
	att=25, dcy=450;
}

int Voice::next(){
	//return ( carrier.phMod(modulator.next()) * gain );
	return ( carrier.next()  * gain)  ;
}

void Voice::triggerEnv(){
	dca->start(att, dcy);
}

void Voice::updateEnvelope(){
	gain = dca->next();
}

void Voice::updateLFO(){

}


//////////////////////////////////////////////////////////////////////////


// Set oscillator parameters
void Voice::setPitch(uint8_t note){
	carrier.setFreq( mtof(note) );
}

void Voice::setCarrierWave(uint8_t w){
	switch(w){
		case 0: 
			carrier.setTable(SIN2048_DATA);
			break; 
		case 1:
			carrier.setTable(TRIANGLE_DIST_CUBED_2048_DATA);
			break;
		case 2:
			carrier.setTable(TRIANGLE_VALVE_2_2048_DATA);
			break;
		case 3:
			carrier.setTable(SAW2048_DATA);
			break;
		case 4:
			carrier.setTable(SQUARE_ANALOGUE512_DATA);
			break;
		case 5:
			carrier.setTable(SQUARE_NO_ALIAS_2048_DATA);
			break;
		case 6:
			carrier.setTable(BROWNNOISE8192_DATA);
			break;
		case 7:
			carrier.setTable(PINKNOISE8192_DATA);
			break;
		default:
			break;
	}
}

void Voice::setModulatorPitch(uint8_t note){
	modulator.setFreq( mtof(note) );
}

void Voice::setModulatorWave(uint8_t w){
	switch(w){
		case 0:
			modulator.setTable(SIN2048_DATA);
			break;
		case 1:
			modulator.setTable(TRIANGLE_DIST_CUBED_2048_DATA);
			break;
		case 2:
			modulator.setTable(TRIANGLE_VALVE_2_2048_DATA);
			break;
		case 3:
			modulator.setTable(SAW2048_DATA);
			break;
		case 4:
			modulator.setTable(SQUARE_ANALOGUE512_DATA);
			break;
		case 5:
			modulator.setTable(SQUARE_NO_ALIAS_2048_DATA);
			break;
		case 6:
			modulator.setTable(BROWNNOISE8192_DATA);
			break;
		case 7:
			modulator.setTable(PINKNOISE8192_DATA);
			break;
		default:
			break;
	}
}

// Set LFO parameters
void Voice::setLFOWave(uint8_t){
	
}

void Voice::setLFOFreq(uint16_t f){
	
}

// Set envelope parameters
void Voice::setEnvAttack(unsigned int a){
	att = a;
	dca->setAttack(att);
}
void Voice::setEnvDecay(unsigned int d){
	dcy = d;
	dca->setDecay(dcy);
}

// Set filter parameters
void Voice::setFilterType(uint8_t t){
	
}
void Voice::setFilterFreq(uint16_t f){
	
}
void Voice::setFilterRes(uint8_t r){
	
}
void setFilterMod(int8_t m){
	
}

// Set fx parameters
void Voice::setFXType(uint8_t t){
	
}
void Voice::setFXAmount(uint8_t a){
	fxamount = a; 
}

// Set modulation parameters
void Voice::setModEnvAmount(int8_t m){
	
}
void Voice::setModulatorAmount(int8_t m){
	
}


#pragma GCC pop_options