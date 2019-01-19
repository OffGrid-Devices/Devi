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

void Voice::init(uint16_t ctrl_rate){
	dca = new Ead(ctrl_rate);
	att=25, dcy=450;
}

void Voice::noteOn(){
	dca->start(att, 65535);
}
void Voice::noteOff(){
	dca->start(0, dcy);
}

void Voice::updateEnvelope(){
	//gain = (depth* dca->next()) >> 8;
	gain = (int)dca->next();
}
void Voice::updateEnvelope(uint8_t depth){
	//gain = (depth* dca->next()) >> 8;
	gain = (int)dca->next(depth);
}

int Voice::next(){
	return gain;
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

#pragma GCC pop_options