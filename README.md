# Devi
Arduino-based synthesizer 

[BOM](https://docs.google.com/spreadsheets/d/11OAxCDL9WJjP-PPryWPdmoXp5gGi14y3Fq-VU7GaQAA/edit?usp=sharing)


# Notes for further development

## Synth Variables

- fixedfreq (bool)
- coarse 
- detune 
- freqrange
- freqfixed
- depth 
- waveform
- attack
- decay 
- algorithm 


## Main Functions

- handleNoteOn
- handleNoteOff
- handleCC
- handleProgramChange
- sendNoteOn
- sendNoteOff
- sendCC
- sendProgramChange
- setMIDICH // runs @setup()
- setProgChangeBehavior // runs @setup()
- savePreset
- loadPreset
- initParams
- updateParams // hardware version of handleCC

## Control Modes

### 0 - Volumes & Mod Depths (RGB=OFF)
- knobs => depth 
- buttons do nothing (or may play individual oscillators)
- LED's show which oscillators are carriers

### 1 - Frequency (RGB=PURPLE)
- button + function => select if oscillator as fixed frequency or not (indicate with LED)
- knob => detune/freqfixed
- button + knob => coarse/freqrange

### 2 - Envelopes (RGB=BLUE)
- button + knob => attack
- knob => decay

### 3 - Waveform (RGB=WHITE)
- knob => waveform  
- buttons + knob6 => set several 
- function + knob => set all

### 4 - Load Preset (RGB=GREEN)
(leds indicate which preset is loaded using a binary representation)
### 5 - Save Preset (RGB=RED)


## FM Algorithms

### 0: six-voice polyphony, single oscillator
(1)|(2)|(3)|(4)|(5)|(6) 

### 1: three-voice polyphony, dual oscillator
(1)+(2)|(3)+(4)|(5)+(6)

### 2: two-voice polyphony, triple oscillator
(1)+(2)+(3)|(4)+(5)+(6)

### 3: three-voice polyphony, FM 2-operators
(2) | (4) | (6)
 |  |  |  |  |
(1) | (3) | (5)

### 4: two-voice polyphony, FM 3-operators
    (2) |     (6)
     |  |      | 
(1)+(3) | (4)+(5)

### 5: two-voice polyphony, FM 3-operators
  (3)   |   (6)
  / \   |   / \
(1)+(2) | (4)+(5)

### 6: two-voice polyphony, FM 3-operators
(2)+(3) | (5)+(6) 
  \ /   |   \ / 
  (1)   |   (4)

### 7: two-voice polyphony, FM 3-operators
(3) | (6)
 |  |  |
(2) | (5)
 |  |  |
(1) | (4)

### 8: monophonic, FM 6-operators
(3) (6)
 |   |
(2) (5)
 |   |
(1)+(4)

### 9: monophonic, FM 6-operators
  (3)     (6)
  / \     / \
(1)+(2) (4)+(5)

### 10: monophonic, FM 6-operators (needs experimentation...is it worth it have 6 stacked oscils when it is possible to change the waveform?)
    (6)             (6)
     |               |
    (5)             (5)
     |       OR      |
(2) (4)             (4)
 |   |               |
(1)+(3)             (3)
                     |
                    (2)
                     |
                    (1) 

### 11: super monophonic, six oscillators
(1)+(2)+(3)+(4)+(5)+(6) 