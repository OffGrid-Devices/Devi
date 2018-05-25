/*!
* \file Voice.h
* \brief Synthesiser voice.
*
* There is a total of six voices.
*\ Each voice has 2 oscillators, 1 LFO, 1 Envelope, 1 FX section and 1 Multimode Filter  
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
	uint8_t pitch = 60; 
	uint16_t filterfreq = 12000;
	uint8_t res = 127;
	protected:
	private:
	Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> carrier;
	Ead* dca;
	ADSR<CONTROL_RATE, AUDIO_RATE> env;
	int gain;
	unsigned int att, dcy;
	uint8_t pitchmin; 
	//functions
	public:
	Voice();
	~Voice();
	void init(uint16_t ctrl_rate, uint8_t pm);
	void setPitch(uint8_t p);
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
	void setPitch();

}; //Voice

#pragma GCC pop_options

#endif //__VOICE_H__
