// This sketch serves to illustrate the functionality of MIDI notes by using a built-in hardware button
// To later replace the button by real MIDI messages
// MIDI part has been disabled/commented

//#include <MIDI.h>

#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/sin2048_int8.h> // sine table for oscillator
#include <mozzi_midi.h>
#include <ADSR.h>


//MIDI_CREATE_DEFAULT_INSTANCE();

// use #define for CONTROL_RATE, not a constant
#define CONTROL_RATE 128 // powers of 2 please

// audio sinewave oscillator
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);

// envelope generator
ADSR <CONTROL_RATE, AUDIO_RATE> envelope;

#define LED 10 // shows if MIDI is being recieved
#define BUTPIN 28 // button to be used as a MIDI note simulator

/*void HandleNoteOn(byte channel, byte note, byte velocity) { 
  aSin.setFreq(mtof(float(note)));
  envelope.noteOn();
  digitalWrite(LED,HIGH);
}
void HandleNoteOff(byte channel, byte note, byte velocity) { 
  envelope.noteOff();
  digitalWrite(LED,LOW);
}*/
void HandleNoteOn(){
  aSin.setFreq(mtof(mozziAnalogRead(A6)>>3));
  envelope.noteOn();
  digitalWrite(LED,HIGH);
}
void HandleNoteOff(){
  envelope.noteOff();
  digitalWrite(LED,LOW);
}

boolean but; // current button value
boolean _but = true; // previous button value (rest=1)

void setup() {
  pinMode(LED, OUTPUT);  
  /*
  // Connect the HandleNoteOn function to the library, so it is called upon reception of a NoteOn.
  MIDI.setHandleNoteOn(HandleNoteOn);  // Put only the name of the function
  MIDI.setHandleNoteOff(HandleNoteOff);  // Put only the name of the function
  // Initiate MIDI communications, listen to all channels (not needed with Teensy usbMIDI)
  MIDI.begin(MIDI_CHANNEL_OMNI);  
  */  
  envelope.setADLevels(255,64);
  envelope.setTimes(50,200,10000,200); // 10000 is so the note will sustain 10 seconds unless a noteOff comes

  aSin.setFreq(440); // default frequency
  startMozzi(CONTROL_RATE); 
}


void updateControl(){
  //MIDI.read();
  but = digitalRead(BUTPIN);
  if(but != _but){
    if(but < 1) HandleNoteOn();
    else HandleNoteOff();
  }
  _but = but; 
  envelope.update();
}


int updateAudio(){
  return (int) (envelope.next() * aSin.next())>>2;
}


void loop() {
  audioHook(); // required here
} 



