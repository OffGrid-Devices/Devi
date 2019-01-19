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
#include <Ead.h>

class Voice
{
	//variables
	public:
	protected:
	private:
		Ead* dca;
		int gain;
		unsigned int att, dcy;
	//functions
	public:
		Voice();
		~Voice();
		
		void init(uint16_t ctrl_rate);
		int next();
		void noteOn(); // attack portion
		void noteOff(); // decay portion
		void updateEnvelope(); // update envelope
		void updateEnvelope(uint8_t depth); // update envelope with depth amount
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
