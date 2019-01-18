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
#include "tables/triangle_dist_cubed_2048_int8.h"
#include "tables/triangle_valve_2_2048_int8.h"
#include "tables/saw2048_int8.h"
#include "tables/square_analogue512_int8.h"
#include "tables/square_no_alias_2048_int8.h"
#include "tables/brownnoise8192_int8.h"
#include "tables/pinknoise8192_int8.h"


class Voice
{
	//variables
	public:
	protected:
	private:
		Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> osc1;
		Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> osc2;
		Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> osc3;
		Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> osc4;
		
		Ead* dca;
		int gain;
		unsigned int att, dcy;
		
		Q15n16 mod1, mod2, mod3;
		uint8_t depth = 255;
		
		float freq[4];

	//functions
	public:
		Voice();
		~Voice();
		
		void init(uint8_t note, uint16_t ctrl_rate);
		int8_t next(uint8_t algo);
		void triggerEnv(); // trigger envelope
		void updateEnvelope(); // update envelope
	
		// Set oscillator parameters 
		//void setPitch(uint8_t note); // set carrier note->frequency
		void setFreq(uint8_t i, float f);
		
		// Set envelope parameters
		void setEnvAttack(unsigned int a); // set envelope attack 
		void setEnvDecay(unsigned int d); // set envelope decay 
	
	protected:
	private:
		Voice( const Voice &c );
		Voice& operator=( const Voice &c );

}; //Voice

#pragma GCC pop_options

#endif //__VOICE_H__
