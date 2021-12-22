# Arduino Sequencer
This project is an arduino based arpeggiator/ sequencer.

## References
### MIDI
- https://itp.nyu.edu/physcomp/labs/labs-serial-communication/lab-midi-output-using-an-arduino/

### Arduino core
- https://www.arduino.cc/en/Tutorial/Foundations

### Ardunio Midi Library
- https://www.arduinolibraries.info/libraries/midi-library
- https://github.com/FortySevenEffects/arduino_midi_library
- https://github.com/FortySevenEffects/arduino_midi_library/releases/tag/4.2

### Ardunio Midi App
- https://www.arduino.cc/en/Tutorial/BuiltInExamples/Midi
- https://create.arduino.cc/projecthub/dra/arduino-midi-arpeggiator-3bd731
- https://create.arduino.cc/projecthub/primvla/cthulhinho-a-midi-sequencer-1ac877

### Display
- https://arduinogetstarted.com/tutorials/arduino-oled

## Operating Instructions
### Mode - Alternate between the musical modes
- ionian (Major)
- dorian (minor)
- phrygian
- lydian
- mixolydian
- aeolian (Natural minor)
- locrian
### Speed - beats per minute
### Key - Root of chords and arpeggios
- C, C#, D, .. Bb, B
### Select - choose arpeggio or sequencer
- Arpeggio
  - ARP-135:  Arpeggio on a triad
  - ARP-1357: Arpeggio on 7th chord
  - ARP-Scale: Arpeggio on all notes in the scale
- Sequence
  - Press 'Rec'
  - Press notes in your sequence
  - Press 'Rec' again to lock in sequence
### Run
- Press once to start arpeggio or sequence playback
- Press again to stop

