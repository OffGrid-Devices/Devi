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
	dca = new Ead(ctrl_rate);
	att=25, dcy=450;
}

int Voice::next(){
	return (carrier.next() * gain);
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
	
}

void Voice::setModulatorPitch(uint8_t note){
	
}

void Voice::setModulatorWave(uint8_t w){
	
}

// Set LFO parameters
void Voice::setLFOWave(uint8_t){
	
}

void Voice::setLFOFreq(uint16_t f){
	
}

// Set envelope parameters
void Voice::setEnvAttack(unsigned int a){
	
}
void Voice::setEnvDecay(unsigned int d){
	
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
void setFXAmount(uint8_t a){
	
}

// Set modulation parameters
void Voice::setFilterModAmount(int8_t m){
	
}
void Voice::setModulatorAmount(int8_t m){
	
}


#pragma GCC pop_options