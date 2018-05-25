/*
 * GLOBALS.h
 *
 * Created: 15-04-2018 11:55:49
 *  Author: tiago
 */ 


#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <Metronome.h>

//COMPILER
#define OPTIMIZATION "O3"

// SYNTH VARIABLES
unsigned int att=25, dcy=150;
uint8_t pitch[6] = {36, 39, 43, 46, 48, 29};

boolean mute[6] = {true, true, true, true, true, true}; // step mute
int8_t step = 0; // current sequencer step
uint8_t steps = 6; // selected number of steps
uint16_t bpm = 4*120, _bpm = bpm;
boolean seqTrigger = 1; // actually runs at twice the audible sequencer rate to turn bpm led indicator on/off (1-triggers envelopes and led on; 0- triggers led off)
Metronome metro(60000/bpm/2); // 120bpm
boolean seqOnOff = true; // is sequencer On ?
uint8_t stepMode = 0; // up, down, up&down, palindrome, random step, random step & pitch
boolean stepDir = 1; // 1-up, 0-down
uint8_t ledPinSequence[6] = {17, 16, 6, 7, 8, 9};

uint8_t filter_mode; // 0-LP, 1-BAND, 1-HP
uint8_t fx_mode; // 0-OFF, 1-<<, 2->>, 3-&, 4-|, 5-^
uint8_t mode = 0; // 0-Sequencer, 1-Trigger, 2-Edit, 3-Save



#endif /* GLOBALS_H_ */