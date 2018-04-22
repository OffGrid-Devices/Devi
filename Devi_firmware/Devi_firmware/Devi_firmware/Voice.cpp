/* 
* Voice.cpp
*
* Created: 22-04-2018 19:25:00
* Author: tiago
*/


#include "Voice.h"

// default constructor
Voice::Voice()
{
	
} //Voice

// default destructor
Voice::~Voice()
{
} //~Voice

void Voice::init(int freq, int ctrl_rate){
	carrier.setTable(SIN2048_DATA);
	carrier.setFreq( mtof(freq) );
	dca = new Ead(ctrl_rate);
}

void Voice::setPitch(uint8_t note){
	carrier.setFreq( mtof(note) );	
}

int Voice::next(){
	return (carrier.next() * gain) >> 7; 
}

void Voice::startDCA(int a, int d){
	att = a; dcy = d;
	dca->start(att, dcy);
}

void Voice::updateEnvelopes(){
	gain = (int) dca->next();
}
