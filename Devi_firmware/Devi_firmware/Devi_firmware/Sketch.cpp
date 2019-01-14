// TODO: make sin table 14-bit instead of 8-bit?

/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
/*End of auto generated code by Atmel studio */

/*
OffGrid-Devices Devi revB : Arduino+Mozzi based synthesizer
firmware version 0.1
by OffGrid-Devices (Tiago Angelo 2018)

Mozzi lib by Tim Barrass
Mozzi AUDIO_RATE = 32768Hz
Mozzi mode = HIFI  
Mozzi version = master(22-04-2018)
*/

#include "DeviHardware.h"

#pragma GCC push_options
#pragma GCC optimize (OPTIMIZATION)

#define CONTROL_RATE 64 // must be called above MozziGuts because of my code architecture....
// 512 is optimal for Ead
// 64 is optimal for ADSR
// 256 is a nice value

#include <MozziGuts.h>
#include <mozzi_rand.h>
#include <mozzi_fixmath.h>
#include <EEPROM.h>

#include "GLOBALS.h"

#include "tables/cos2048_int8.h" // table for Oscils to play
#include <Oscil.h>

//Beginning of Auto generated function prototypes by Atmel Studio
void updateControl();
int updateAudio();

void readRotary();
//End of Auto generated function prototypes by Atmel Studio



//////////////////////////////////////////////////////////////////////////
// CLASSES //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> osc1(COS2048_DATA);
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> osc2(COS2048_DATA);
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> osc3(COS2048_DATA);
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> osc4(COS2048_DATA);

Q15n16 mod1, mod2, mod3;
uint8_t depth = 255; 
//////////////////////////////////////////////////////////////////////////
// MAIN FUNCTIONS ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void setup(){
	osc1.setFreq(440);
	osc2.setFreq(220);
	osc3.setFreq(110);
	osc4.setFreq(55);
	
	startMozzi(CONTROL_RATE);
	setupFastAnalogRead(FASTEST_ADC);
}

void updateControl(){
	readRotary();

	
	osc1.setFreq(mozziAnalogRead(A0) + 30);
	osc2.setFreq(mozziAnalogRead(A1) + 30);
	osc3.setFreq(mozziAnalogRead(A2) + 30);
	osc4.setFreq(mozziAnalogRead(A3) + 30);
}

int updateAudio(){ 
	int sig;
	switch(rotary){ // CHECK IF CODE IS CORRECT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
	return sig;
	// 14-bit output: -8192 to 8191
}

void loop(){
  audioHook();
}

//////////////////////////////////////////////////////////////////////////
// SETUP ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// READ /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void readRotary(){
	_rotary = rotary; // set previous values for state change detection
	for(int i = 0; i < 8; i++){
		if( bit_get(PINC, BIT(i)) ) rotary = i; 
	}
	for(int i = 0; i < 4; i++){
		if( bit_get(PIND, BIT(i)) ) rotary = i+8;
	}
}
//////////////////////////////////////////////////////////////////////////
// MIDI /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// MEM ///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// UTILITIES ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

#pragma GCC pop_options
