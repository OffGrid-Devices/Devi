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
	Ead* dca;
	//ADSR<CONTROL_RATE, AUDIO_RATE> env; 
	int gain;
	unsigned int att, dcy;
	//functions
	public:
	Voice();
	~Voice();
	void init(uint8_t pitch, uint16_t ctrl_rate);
	void setPitch(uint8_t freq);
	int next();
	void triggerEnv();
	void updateEnvelopes();
	
	protected:
	private:
	Voice( const Voice &c );
	Voice& operator=( const Voice &c );

}; //Voice

#pragma GCC pop_options

#endif //__VOICE_H__
