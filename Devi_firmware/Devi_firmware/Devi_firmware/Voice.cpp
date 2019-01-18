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

void Voice::init(uint8_t note, uint16_t ctrl_rate){
	osc1.setTable(SIN2048_DATA);
	osc2.setTable(SIN2048_DATA);
	osc3.setTable(SIN2048_DATA);
	osc4.setTable(SIN2048_DATA);
	
	freq[0] = 440;
	freq[1] = 220;
	freq[2] = 110;
	freq[3] = 55;

	osc1.setFreq( freq[0] );
	osc2.setFreq( freq[1] );
	osc3.setFreq( freq[2] );
	osc4.setFreq( freq[3] );
	
	dca = new Ead(ctrl_rate);
	att=25, dcy=450;
}

int8_t Voice::next(uint8_t algo){
	int sig;
	switch(algo){ 
		case 0: 
		/*	[1] [2] [3] [4]	*/
			sig = ( osc1.next() 
				  + osc2.next()
				  + osc3.next()
				  + osc4.next()
				) << 3;
		break;
		
		case 1:
		/*	  [4]
			   |		
		[1][2][3]	*/	
			mod3 = osc4.next() * depth;
			sig = ( osc1.next()
				  + osc2.next()
				  + osc3.phMod(mod3)
			)<<3;
		break;
		
		/*	  [4]
			 / |
		[1][2][3]	*/
		case 2:
			mod3 = osc4.next() * depth;
			sig = ( osc1.next()
				  + osc2.phMod(mod3)
				  + osc3.phMod(mod3)
				)<<3;
		break;	
		case 3:
		/* [4]
		 /  |  \
		[1][2][3]	*/
			mod3 = osc4.next() * depth;
			sig = ( osc1.phMod(mod3)
				  + osc2.phMod(mod3)
				  + osc3.phMod(mod3)
				)<<3;
		break;
		
		case 4: 
		/* [4]
			|
		   [3]
			|
		[1][2] */
		mod2 = osc3.phMod(osc4.next() * depth) * depth; 
		sig = ( osc1.next() 
			  + osc2.phMod(mod2)
			) << 4; 
		break;
		
		case 5:
		/* [2][4]
			|  |
		   [1][3]	*/
			mod1 = osc2.next() * depth;
			mod3 = osc4.next() * depth;
			sig = ( osc1.phMod(mod1)
				  + osc3.phMod(mod3)
				)<<4;
		break;
		
		case 6:
		/* [2][4]
		    | /|
	       [1][3] */
			mod1 = ( (osc2.next() + osc4.next())>>1 )*depth;
			mod3 = osc4.next() * depth;
			sig = ( osc1.phMod(mod1)
				+ osc3.phMod(mod3)
				)<<4;
		break;
		
		case 7:
		/* [2][4]
		    | \|
		   [1][3]	*/
			mod1 = osc2.next() * depth;
			mod3 = ( (osc2.next()+osc4.next())>>1 )*depth;
			sig = ( osc1.phMod(mod1)
				  + osc3.phMod(mod3)
				)<<4;
		break;
		
		case 8:
		/*  [4]
			 |
			[3]
			/  \
		   [1][2]	*/
			mod1 = osc3.phMod( osc4.next()*depth )*depth;
			sig = ( osc1.phMod(mod1)
				  + osc2.phMod(mod1)
				)<<4;
		break;
		
		case 9:
		/*  [4]
		   /   \
		  [2] [3]
		   \   /
			[1]		*/
			mod2 = osc4.next() * depth; 
			mod1 = ( ( osc2.phMod(mod2) + osc3.phMod(mod2) )>>1 )*depth;  
			sig = ( osc1.phMod(mod1) )<<5;
		break;
		
		case 10:
		/*  [2][3][4]
		     \  |  /
			   [1]		*/
			mod1 = ( ( osc2.next()+osc3.next()+osc4.next() )>>2 )*depth; 
			// note: dividing by 3.f will cause some glitches, so I used >>2 that goes from 0 to 191
			sig = ( osc1.phMod(mod1) )<<5;
		break;
		
		case 11:
		/* [4]
		    |
		   [3]
		    | 
		   [2]
		    |
		   [1]		*/
			mod3 = osc4.next() * depth;
			mod2 = osc3.phMod(mod3) * depth;
			mod1 = osc2.phMod(mod2) *depth;
			sig = ( osc1.phMod(mod1) )<<5;
		break;
		
	}
	return sig >> 6;
	// 8-bit output: -256 to 255
}

void Voice::triggerEnv(){
	dca->start(att, dcy);
}

void Voice::updateEnvelope(){
	gain = dca->next();
}




//////////////////////////////////////////////////////////////////////////


// Set oscillator parameters
void Voice::setFreq(uint8_t i, float f){
	switch(i){
		case 1:	osc1.setFreq(f); break;
		case 2:	osc2.setFreq(f); break;
		case 3:	osc3.setFreq(f); break;
		case 4:	osc4.setFreq(f); break;
		default: break;
	}
}

/*void Voice::setPitch(uint8_t note){
	carrier.setFreq( mtof(note) );
}

void Voice::setCarrierWave(uint8_t w){
	switch(w){
		case 0: 
			carrier.setTable(SIN2048_DATA);
			break; 
		case 1:
			carrier.setTable(TRIANGLE_DIST_CUBED_2048_DATA);
			break;
		case 2:
			carrier.setTable(TRIANGLE_VALVE_2_2048_DATA);
			break;
		case 3:
			carrier.setTable(SAW2048_DATA);
			break;
		case 4:
			carrier.setTable(SQUARE_ANALOGUE512_DATA);
			break;
		case 5:
			carrier.setTable(SQUARE_NO_ALIAS_2048_DATA);
			break;
		case 6:
			carrier.setTable(BROWNNOISE8192_DATA);
			break;
		case 7:
			carrier.setTable(PINKNOISE8192_DATA);
			break;
		default:
			break;
	}
}

void Voice::setModulatorPitch(uint8_t note){
	modulator.setFreq( mtof(note) );
}

void Voice::setModulatorWave(uint8_t w){
	switch(w){
		case 0:
			modulator.setTable(SIN2048_DATA);
			break;
		case 1:
			modulator.setTable(TRIANGLE_DIST_CUBED_2048_DATA);
			break;
		case 2:
			modulator.setTable(TRIANGLE_VALVE_2_2048_DATA);
			break;
		case 3:
			modulator.setTable(SAW2048_DATA);
			break;
		case 4:
			modulator.setTable(SQUARE_ANALOGUE512_DATA);
			break;
		case 5:
			modulator.setTable(SQUARE_NO_ALIAS_2048_DATA);
			break;
		case 6:
			modulator.setTable(BROWNNOISE8192_DATA);
			break;
		case 7:
			modulator.setTable(PINKNOISE8192_DATA);
			break;
		default:
			break;
	}
}*/

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