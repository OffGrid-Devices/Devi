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

// INCLUDES
#include <Metronome.h>

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

// DEFINITIONS
#define NUMVOICES 2
#define MINPITCH 24
#define MAXFREQ 12000 // filter maximum frequency



// STORED VARIABLES (struct size = 128Bytes x 12 presets = 1536Bytes) ArduinoMega EEPROM = 4096Bytes
struct Preset{ 
//////////////////////////////////////////////////////////////////////////
// SEQUENCER VARIABLES //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
boolean mute[6] = {true, true, true, true, true, true}; // step mute
uint8_t steps = 6; // selected number of steps
uint8_t stepMode = 0; // up, down, up&down, palindrome, random step, random step & pitch

//////////////////////////////////////////////////////////////////////////
// SYNTH VOICE VARIABLES ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
// Carrier oscillator
uint8_t pitch[6] = {36, 39, 43, 46, 48, 29}; // carrier pitch
uint8_t wave[8]; // carrier waveform: 0-sin, 1-tri, 2-rampup, 3-rampdown, 4-square, 5-noise
// Modulator oscillator
uint8_t modpitch[6] = {36, 39, 43, 46, 48, 29}; // modulator pitch	
uint8_t modwave[8]; // carrier waveform: 0-sin, 1-tri, 2-rampup, 3-rampdown, 4-square, 5-noise
// Modulation parameters
int8_t modamount[6]; // modulation amount
int8_t envamount[6]; // envelope to modulation amount 
// Envelope 
unsigned int att[6] = {25, 25, 25, 25, 25, 25}; 
unsigned int dcy[6] = {150, 150, 150, 150, 150, 150}; 
// FX
uint8_t fxtype[6]; // 0-OFF, 1-<<, 2->>, 3-&, 4-|, 5-^
uint8_t fxamount[6]; // fx parameter/amount
// FILTER 
uint8_t filtertype[6];// 0-LP, 1-BAND, 1-HP, 2-NOTCH
uint16_t filterfreq[6] = {12000, 12000, 12000, 12000, 12000, 12000, }; // filter cutoff frequency
uint8_t filterres[6] = {127, 127, 127, 127, 127, 127}; // filter resonance
int8_t filtermod[6]; // LFO to filter modulation amount	
// LFO
uint16_t lfofreq[6] = {4, 4, 4, 4, 4, 4}; // lfo frequency
uint8_t lfowave[8]; // lfo waveform: 0-sin, 1-tri, 2-rampup, 3-rampdown, 4-square, 5-noise 
};



// NON-STORED VARIABLES
uint8_t rotary, _rotary; // current and previous rotary switch value 
uint8_t mode = 0; // 0-Sequencer, 1-Trigger, 2-Edit, 3-Save

uint16_t bpm = 4*120, _bpm = bpm; // bpm and previous bpm 
Metronome metro(60000/bpm/2); // 120bpm
boolean seqTrigger = 1; // actually runs at twice the audible sequencer rate to turn bpm led indicator on/off (1-triggers envelopes and led on; 0- triggers led off)
int8_t step = 0; // current sequencer step
boolean stepDir = 1; // 1-up, 0-down //TODO: store stepDir variable????
boolean seqOnOff = true; // is sequencer On? //TODO: store seqOnOff variable????

uint8_t ledPinSequence[6] = {17, 16, 6, 7, 8, 9};


#pragma GCC pop_options

#endif /* GLOBALS_H_ */