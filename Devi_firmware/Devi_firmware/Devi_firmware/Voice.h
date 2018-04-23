/*
* Voice.h
*
* Created: 22-04-2018 19:25:00
* Author: tiago
*/


#ifndef __VOICE_H__
#define __VOICE_H__

#pragma GCC push_options
#pragma GCC optimize (OPTIMIZATION)

#include <mozzi_config.h>
#include <Oscil.h>
#include <Ead.h>
#include <ADSR.h>
#include <mozzi_midi.h>
#include "tables/sin2048_int8.h"

class Voice
{
	//variables
	public:
	protected:
	private:
	Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> carrier;
	Ead* dca;
	ADSR<CONTROL_RATE, AUDIO_RATE> env; 
	int gain;
	unsigned int att, dcy;
	//functions
	public:
	Voice();
	~Voice();
	void setPitch(uint8_t freq);
	int next();
	void startDCA();
	void updateEnvelopes();
	void noteOn();
	void noteOff();
	void updateEnv();
	
	protected:
	private:
	Voice( const Voice &c );
	Voice& operator=( const Voice &c );

}; //Voice

#pragma GCC pop_options

#endif //__VOICE_H__