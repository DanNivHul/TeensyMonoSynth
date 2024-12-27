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
  AudioMemory(60);
  usbMIDI.setHandleControlChange(myControlChange);
  usbMIDI.setHandleNoteOff(myNoteOff);
  usbMIDI.setHandleNoteOn(myNoteOn);
  usbMIDI.setHandlePitchChange(myPitchBend);

  MIDI.begin();

  MIDI.setHandleNoteOn(myNoteOn);
  MIDI.setHandleNoteOff(myNoteOff);
  MIDI.setHandlePitchBend(myPitchBend);
  MIDI.setHandleControlChange(myControlChange);
  
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.7);

  // OSC VOLT PER OCTAVE
  dc_osc_freq.amplitude(0.0);

  // OSCILLATOR A
  osc_A.begin(WAVEFORM_BANDLIMIT_SAWTOOTH);
  osc_A.amplitude(0.1);
  osc_A.frequency(440.0);
  osc_A.frequencyModulation(10.0);

  dc_osc_A_pulse_width.amplitude(0.5);

  mixer_osc_A_freq.gain(0, 1.0);  // Note frequency
  mixer_osc_A_freq.gain(1, 1.0);  // Lfo
  mixer_osc_A_freq.gain(2, 0.0);  // Not used
  mixer_osc_A_freq.gain(3, 0.0);  // Not used

  // OSCILLATOR B
  osc_B.begin(WAVEFORM_BANDLIMIT_SAWTOOTH);
  osc_B.amplitude(0.1);
  osc_B.frequency(440.0);
  osc_B.frequencyModulation(10.0);

  dc_osc_B_pulse_width.amplitude(0.75);

  dc_detune.amplitude(detune_amount);

  mixer_osc_B_freq.gain(0, 1.0);  // Note frequency
  mixer_osc_B_freq.gain(1, 1.0);  // Lfo
  mixer_osc_B_freq.gain(2, 1.0);  // Detune
  mixer_osc_B_freq.gain(3, 0.0);  // Not used

  // OSCILLATOR SUB
  osc_sub.begin(WAVEFORM_SINE);
  osc_sub.amplitude(0.2);
  osc_sub.frequency(440.0);
  osc_sub.frequencyModulation(10.0);

  dc_osc_sub_freq_offset.amplitude(-0.1);

  mixer_osc_sub_freq.gain(0, 1.0);  // Note frequency
  mixer_osc_sub_freq.gain(1, 1.0);  // Lfo
  mixer_osc_sub_freq.gain(2, 1.0);  // Offset (i.e. one octave down)
  mixer_osc_sub_freq.gain(3, 0.0);  // Not used

  // OSCILLATOR MOD
  amp_lfo_osc_depth.gain(0.0);

  // NOISE GENERATOR
  pink_noise.amplitude(0.1);

  // MIXER
  mixer.gain(0, 0.707 * MAX_OSC_LEVEL); // Osc A
  mixer.gain(1, 0.707 * MAX_OSC_LEVEL); // Osc B
  mixer.gain(2, 0.2); // Osc Sub
  mixer.gain(3, 0.1); // Noise

  // FILTER
  filter.frequency(12000.0);
  filter.resonance(1.0);
  filter.octaveControl(0.0);

  // FILTER ENV
  envelope_filter.attack(1.0);
  envelope_filter.decay(500.0);
  envelope_filter.sustain(0.0);
  envelope_filter.release(0.0);

  // FILTER TYPE - LOW PASS / BAND PASS
  mixer_filter_output.gain(0, 1.0); // Low pass
  mixer_filter_output.gain(1, 0.0); // Band pass
  mixer_filter_output.gain(2, 0.0); // Not used
  mixer_filter_output.gain(3, 0.0); // Not used

  // FILTER MOD
  dc_filter_envelope_depth.amplitude(0.0);
  amp_filter_lfo_depth.gain(0.0);

  mixer_filter_mod.gain(0, 1.0); // Lfo
  mixer_filter_mod.gain(1, 1.0); // Env
  mixer_filter_mod.gain(2, 0.0); // Not used
  mixer_filter_mod.gain(3, 0.0); // Not used

  // AMP ENV
  envelope_amp.attack(1.0);
  envelope_amp.decay(0.0);
  envelope_amp.sustain(1.0);
  envelope_amp.release(500.0);

  // LFO
  lfo.begin(WAVEFORM_TRIANGLE);
  lfo.amplitude(0.5);
  lfo.frequency(0.1);
  lfo.offset(0.5);

  envelope_lfo_delay.attack(0.0);
  envelope_lfo_delay.decay(0.0);
  envelope_lfo_delay.sustain(1.0);
  envelope_lfo_delay.release(0.0);
  envelope_lfo_delay.releaseNoteOn(0.0);

  // OUTPUT LEVEL
  amp_output.gain(0.7);


  Serial.println("Hello World");
}


void loop() {
  usbMIDI.read();
  MIDI.read();
}