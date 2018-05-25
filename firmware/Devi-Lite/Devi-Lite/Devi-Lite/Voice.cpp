#pragma GCC push_options
#pragma GCC optimize (OPTIMIZATION)

#include "Voice.h"

// default constructor
Voice::Voice()
{
	
} //Voice

// default destructor
Voice::~Voice()
{
} //~Voice

void Voice::init(uint16_t ctrl_rate, uint8_t pm){
	carrier.setTable(SIN2048_DATA);
	carrier.setFreq( mtof(pitch) );
	dca = new Ead(ctrl_rate);
	att=25, dcy=450;
	env.setADLevels(255, 255);
	env.setTimes(att, 25, 500, dcy);
	pitchmin = pm;
	setPitch();
}
void Voice::setPitch(){
	pitch = pitch - pitchmin;
}
void Voice::setPitch(uint8_t p){
	pitch = p;
	carrier.setFreq( mtof( pitch+pitchmin) );
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