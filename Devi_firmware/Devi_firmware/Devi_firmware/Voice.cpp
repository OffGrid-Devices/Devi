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

void Voice::init(uint8_t pitch, uint16_t ctrl_rate){
	carrier.setTable(SIN2048_DATA);
	carrier.setFreq( mtof(pitch) );
	dca = new Ead(ctrl_rate);
	att=25, dcy=450;
	
	env.setADLevels(255, 255);
	env.setTimes(att, 25, 500, dcy);  
}

void Voice::setPitch(uint8_t note){
	carrier.setFreq( mtof(note) );
}

int Voice::next(){
	return (carrier.next() * gain);
	//return carrier.next() * env.next();
}

void Voice::startDCA(){
	dca->start(att, dcy);
}

void Voice::updateEnvelopes(){
	gain = dca->next();
}

void Voice::noteOn(){
	env.noteOn();
}

void Voice::noteOff(){
	env.noteOff();	
}

void Voice::updateEnv(){
	env.update();
}

#pragma GCC pop_options