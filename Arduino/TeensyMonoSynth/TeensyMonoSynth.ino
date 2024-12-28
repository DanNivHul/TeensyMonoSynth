#include <MIDI.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// Local includes
#include "AudioPatch.h"
#include "Constants.h"
#include "Globals.h"



// MIDI
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);


void setup() {
  Serial.begin(115200);
  
  usbMIDI.setHandleControlChange(myControlChange);
  usbMIDI.setHandleNoteOff(myNoteOff);
  usbMIDI.setHandleNoteOn(myNoteOn);
  usbMIDI.setHandlePitchChange(myPitchBend);

  MIDI.begin();

  MIDI.setHandleNoteOn(myNoteOn);
  MIDI.setHandleNoteOff(myNoteOff);
  MIDI.setHandlePitchBend(myPitchBend);
  MIDI.setHandleControlChange(myControlChange);
  
  setupAudio();

  Serial.println("Hello World");
}


void loop() {
  usbMIDI.read();
  MIDI.read();
}