/*
* Voice.h
*
* Created: 22-04-2018 19:25:00
* Author: tiago
*/


#ifndef __VOICE_H__
#define __VOICE_H__

#include <Oscil.h>
#include <Ead.h>
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
	int gain;
	unsigned int att=25, dcy=450;
	//functions
	public:
	Voice();
	~Voice();
	void init(int freq, int ctrl_rate);
	void setPitch(uint8_t freq);
	int next();
	void startDCA(int a, int d);
	void updateEnvelopes();
	protected:
	private:
	Voice( const Voice &c );
	Voice& operator=( const Voice &c );

}; //Voice

#endif //__VOICE_H__
