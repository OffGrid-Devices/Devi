/*
 * GLOBALS.h
 *
 * Created: 15-04-2018 11:55:49
 *  Author: tiago
 */ 


#ifndef GLOBALS_H_
#define GLOBALS_H_

// COMPILER
#define OPTIMIZATION "O3"
#pragma GCC push_options
#pragma GCC optimize (OPTIMIZATION)
// MACROS
#define bit_get(p,m) ((p) & (m))
#define bit_set(p,m) ((p) |= (m))
#define bit_clear(p,m) ((p) &= ~(m))
#define BIT(x)(0x01 << (x))
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif
// INCLUDES
#include <Metronome.h>


// STORED VARIABLES

//////////////////////////////////////////////////////////////////////////
// SEQUENCER VARIABLES //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
boolean mute[6] = {true, true, true, true, true, true}; // step mute
int8_t step = 0; // current sequencer step // TODO: store step variable????
uint8_t steps = 6; // selected number of steps
uint16_t bpm = 4*120, _bpm = bpm; // TODO: store _bpm variable????
boolean seqOnOff = true; // is sequencer On? //TODO: store seqOnOff variable????
uint8_t stepMode = 0; // up, down, up&down, palindrome, random step, random step & pitch
boolean stepDir = 1; // 1-up, 0-down //TODO: store stepDir variable????

//////////////////////////////////////////////////////////////////////////
// SYNTH VOICE VARIABLES ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
unsigned int att=25, dcy=150;
uint8_t pitch[6] = {36, 39, 43, 46, 48, 29};
uint8_t filter_mode; // 0-LP, 1-BAND, 1-HP
uint8_t fx_mode; // 0-OFF, 1-<<, 2->>, 3-&, 4-|, 5-^

// NON-STORED VARIABLES
uint8_t mode = 0; // 0-Sequencer, 1-Trigger, 2-Edit, 3-Save
Metronome metro(60000/bpm/2); // 120bpm
uint8_t ledPinSequence[6] = {17, 16, 6, 7, 8, 9};
boolean seqTrigger = 1; // actually runs at twice the audible sequencer rate to turn bpm led indicator on/off (1-triggers envelopes and led on; 0- triggers led off)
uint8_t rotary, _rotary; // current and previous rotary switch value 


#pragma GCC pop_options

#endif /* GLOBALS_H_ */