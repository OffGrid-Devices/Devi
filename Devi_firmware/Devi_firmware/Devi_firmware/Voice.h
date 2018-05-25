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
#include <mozzi_midi.h>
#include <StateVariable.h>
// wavetables 
#include "tables/sin2048_int8.h"
#include "tables/triangle_valve_2_2048_int8.h"
#include "tables/triangle_dist_cubed_2048_int8.h"
#include "tables/saw2048_int8.h"
#include "tables/square_no_alias_2048_int8.h"
#include "tables/pinknoise8192_int8.h"

class Voice
{
	//variables
	public:
	protected:
	private:
	Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> carrier;
	Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> modulator;
	Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> lfo;
	StateVariable <BANDPASS> svf; // can be LOWPASS, BANDPASS, HIGHPASS or NOTCH
	Ead* dca;
	int gain;
	unsigned int att, dcy;
	//functions
	public:
	Voice();
	~Voice();
	void init(uint8_t note, uint16_t ctrl_rate);
	int next();
	void triggerEnv(); // trigger envelope
	void updateEnvelope(); // update envelope
	void updateLFO(); // update LFO
	
	// Set oscillator parameters 
	void setPitch(uint8_t note); // set carrier note->frequency
	void setCarrierWave(uint8_t w);
	void setModulatorPitch(uint8_t note);
	void setModulatorWave(uint8_t w); 
	// Set LFO parameters
	void setLFOWave(uint8_t);
	void setLFOFreq(uint16_t f);
	// Set envelope parameters
	void setEnvAttack(unsigned int a); // set envelope attack 
	void setEnvDecay(unsigned int d); // set envelope decay 
	// Set filter parameters
	void setFilterType(uint8_t t);
	void setFilterFreq(uint16_t f);
	void setFilterRes(uint8_t r);
	void setFilterMod(int8_t m);
	// Set fx parameters 
	void setFXType(uint8_t t);
	void setFXAmount(uint8_t a);
	// Set modulation parameters 
	void setFilterModAmount(int8_t m);
	void setModulatorAmount(int8_t m);
	 
	
	protected:
	private:
	Voice( const Voice &c );
	Voice& operator=( const Voice &c );

}; //Voice

#pragma GCC pop_options

#endif //__VOICE_H__
