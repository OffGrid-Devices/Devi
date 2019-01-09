// Basic 2-Operator Frequency Modulation

#include <MozziGuts.h>
#include <Oscil.h>
#include <tables/cos2048_int8.h> // table for Oscils to play
#include <mozzi_midi.h>
#include <mozzi_fixmath.h>

#define CONTROL_RATE 256 // powers of 2 please

Oscil<COS2048_NUM_CELLS, AUDIO_RATE> aCarrier(COS2048_DATA);
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> aModulator(COS2048_DATA);

uint8_t depth = 255; // modulation depth

void setup(){
  startMozzi(CONTROL_RATE);  
  aCarrier.setFreq(440);
  aModulator.setFreq(220);
}

void updateControl(){}

int updateAudio(){
  Q15n16 modulation = aModulator.next() * depth;
  return (int)aCarrier.phMod(modulation)     <<6;
}

void loop(){
  audioHook();
}
