// ====================================================================================================
// TODO - HIGH PRIORITY
// ====================================================================================================
// todo - change square to pulse for Osc A and Osc B and add pulse width ccs for both (on second thought, if you have lfo and envelope to pulse width, do you need manual set of pulse width? I guess helpful for testing?)
// todo - lfo to pulse width. cc for depth
// todo - envelope to pulse width. cc for depth
// todo - expose full adsr parameters to cc. filter and amp share same settings
// todo - envelope to osc pitch
// todo - set volume to 1
// todo - sub waveform select (square or 25% pulse?)
// done - add bandpass option for filter
// done - lfo to osc pitches
// done - option for legato mode (retrigger envelopes vs don't)
// done - better note on / off. at the moment. store previous notes in buffer and return to them if note off not received
// done - glide


// ====================================================================================================
// TODO - MID PRIORITY
// ====================================================================================================
// todo - finalise glide times. or alternatively have a constant glide time and either turn it on or off
// todo - should lfo to osc be bipolar? currently it is unipolar?
// todo - fine tune range for lfo to osc. currently goes up to 1 octave, but not sure how useful that is
// todo - add detune to 3rd, 5th, etc?
// todo - detune unipolar
// todo - pitch bend
// todo - mod wheel to either filter cutoff or lfo depth?
// todo - note velocity to volume. cc for depth
// todo - note velocity to filter cutoff. cc for depth
// todo - filter cutoff envelope bipolar. 
// todo - filter cutoff lfo bipolar
// todo - white noise as lfo source
// todo - lfo option where each note on triggers a new random value and sustains it until the next note on 
// todo - send midi over usb to update web programmer
// todo - logical operator distortion - type and crossfade distortion amount
// todo - x-mod of oscillators
// done - crossfade between osc A and osc B using constant power instead of linear crossfade


// ====================================================================================================
// TODO - LOW PRIORITY
// ====================================================================================================
// todo - option for auto-glide (always glide vs only glide when notes overlap)
// todo - finetune lfo rate range. 
// todo - option to reset phase of osc when note on event is triggered. cc for that
// todo - option to reset lfo phase when note on event is triggered. cc for that
// todo - sync lfo to midi clock. rate becomes clock divider
// todo - someway of storing presets? online editor
// todo - led for midi rx
// todo - led for lfo rate
// todo - midi channel rx. set by web programmer. store and load in eeprom.
// todo - poly aftertouch? a
// todo - unison option?






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

  dc_detune.amplitude(0.001);

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

void myNoteOn(byte channel, byte note, byte velocity) {
  Serial.println("Note on");

  
  int8_t new_note_index = -1;
  for (int8_t i = 0; i < HELD_NOTES_COUNT; i++) {
    // If new note is already being held - Ignore new note. Do not do anything. Return.
    if (held_notes[i] == note) {
      return;
    }

    // Find the first unused slot in the note buffer
    if (held_notes[i] == 0 && new_note_index == -1) {
      new_note_index = i;
    }
  }  

  // If notes buffer is full - Ignore new note. Do not do anything. Return.
  if (new_note_index == -1) {
    return;
  }

  // Store new note
  held_notes[new_note_index] = note;
  
  // AudioNoInterrupts();  // Disable the audio library update interrupt. This allows more than 1 object's settings to be changed simultaneously.

  if (new_note_index == 0) {
    // If no other note is being held - Play new note immediately. Do trigger envelope.
    dc_osc_freq.amplitude(NOTE_FREQ_DC[note], 0.0);
    envelope_amp.noteOn();
    envelope_filter.noteOn();
    envelope_lfo_delay.noteOn();
  } else {
    // If a note is being held - Glide to new note. 
    dc_osc_freq.amplitude(NOTE_FREQ_DC[note], glide_time_ms);
    
    // If legato mode is enabled - do not trigger envelope.
    // If legato mode is not enabled - do trigger envelope.
    if (!is_legato_enabled) {
      envelope_amp.noteOn();
      envelope_filter.noteOn();
      envelope_lfo_delay.noteOn();
    }
  }
  
  // AudioInterrupts();  // Enable the audio library update interrupt. Any settings changed will all take effect at the same time.
}

void myNoteOff(byte channel, byte note, byte velocity) {
  Serial.println("Note off");

  // Check if off note is in note buffer and find most recently held note
  int8_t off_note_index = -1;
  int8_t most_recently_held_note_index = -1;
  for (int8_t i = 0; i < HELD_NOTES_COUNT; i++) {
    if (held_notes[i] == 0) {
      break;
    }
     
    if (held_notes[i] == note && off_note_index == -1) {
      off_note_index = i;
    }

    most_recently_held_note_index = i;
  }  

  // If off note not in buffer - Ignore it. Do not do anything.
  if (off_note_index == -1) {
    return;
  }

  // AudioNoInterrupts();  // Disable the audio library update interrupt. This allows more than 1 object's settings to be changed simultaneously.

  // If the released note is the last note played - update the audio
  if (most_recently_held_note_index == off_note_index) {
    if (most_recently_held_note_index > 0) {
      // If another note is being held - Glide to the next most recently pressed note. Do not trigger envelope.
      uint8_t next_most_recently_held_note = held_notes[most_recently_held_note_index - 1];
      dc_osc_freq.amplitude(NOTE_FREQ_DC[next_most_recently_held_note], glide_time_ms);
    } else {
      // If no other note is being held - Trigger envelope note off.
      envelope_amp.noteOff();
      envelope_filter.noteOff();
    }
  }

  // AudioInterrupts();  // Enable the audio library update interrupt. Any settings changed will all take effect at the same time.
  
  // Remove off note from note buffer
  held_notes[off_note_index] = 0;

  // Re-order buffer
  for (int8_t i = 0; i < HELD_NOTES_COUNT; i++) {
    if (held_notes[i] == 0 && (i + 1) < HELD_NOTES_COUNT) {
      held_notes[i] = held_notes[i + 1];
      held_notes[i + 1] = 0;
    }
  } 

}

  // todo - implement bend
void myPitchBend(byte channel, int bend) {
  // float bendF = bend;
  // float bendRange = 1.0;
  // bendF = bendF / 8192;
  // bendF = bendF * bendRange;
  // bendF = bendF / 12;
  // float bendFactor = pow(2, bendF);
}


void myControlChange(byte channel, byte control, byte value) {
  Serial.print("Channel: ");
  Serial.print(channel);
  Serial.print(", cc: ");
  Serial.print(control);
  Serial.print(", value: ");
  Serial.println(value);

  switch (control) {

    case 10: { // Osc Waveshapes
        if (value < 43) {
          osc_A.begin(WAVEFORM_BANDLIMIT_SAWTOOTH);
          osc_B.begin(WAVEFORM_BANDLIMIT_SAWTOOTH);
        } else if (value < 87) {
          osc_A.begin(WAVEFORM_BANDLIMIT_SAWTOOTH);
          osc_B.begin(WAVEFORM_BANDLIMIT_PULSE);
        } else {
          osc_A.begin(WAVEFORM_BANDLIMIT_SQUARE);
          osc_B.begin(WAVEFORM_BANDLIMIT_PULSE);
        }
      } 
      break;

    case 11: { // Osc B - Detune
        float detune_level = value / 127.0 * 0.008 - 0.004; // gives a range of just less than -0.5 semitone to +0.5 semitone
        dc_detune.amplitude(detune_level);
      }
      break;

    case 12: { // Osc A - Pulse Width
    //dc_osc_A_pulse_width
        // todo 
        // dc_osc_A_pulse_width.amplitude(detune_level);
      }
      break;

    case 13: { // Osc B - Pulse Width
        // todo
        // dc_detune.amplitude(detune_level);
      }
      break;

    case 14: { // Glide time
        glide_time_ms = (float) (ENV_TIMES_MS[value] - 1);
      }
      break;

    case 15: { // Legato
        is_legato_enabled = value < 64;
      }
      break;

    case 16: { // Osc lfo depth
        amp_lfo_osc_depth.gain(POWER[value] * MAX_OSC_LFO_AMPLITUDE);
      }
      break;

    case 20: { // Mix between Osc A and Osc B
        float osc_A_level = CONSTANT_POWER[127 - value] * MAX_OSC_LEVEL;
        float osc_B_level = CONSTANT_POWER[value] * MAX_OSC_LEVEL;
        mixer.gain(0, osc_A_level);
        mixer.gain(1, osc_B_level);
      }
      break;

    case 21: // Sub level
        osc_sub.amplitude(value / 127.0);
      break;

    case 22: // Noise level
        pink_noise.amplitude(value / 127.0 / 5.0);
      break;

    case 30: { // Filter cutoff frequency
        uint16_t filter_cutoff_frequency_hz = FILTER_CUTOFF_FREQS_HZ[value * 2];
        filter.frequency(filter_cutoff_frequency_hz);
        float filter_octave = log2f(12000.0 / (float) filter_cutoff_frequency_hz);
        filter.octaveControl(filter_octave);
      }
      break;

    case 31: // Filter resonance
      filter.resonance((4.3 * (value / 127.0)) + 0.7);  // todo - better formula for mapping midi values
      break;

    case 32: // Filter env depth 
      filter_envelope_depth_cc_value = value;
      updateFilterMods();
      break;

    case 33: // Filter lfo depth 
      filter_lfo_depth_cc_value = value;
      updateFilterMods();
      break;

    case 34: // Filter type - low pass / band pass 
      if (value < 64) {
        // Use low pass filter
        mixer_filter_output.gain(0, 1.0); // Low pass
        mixer_filter_output.gain(1, 0.0); // Band pass
      } else {
        // Use band pass filter
        mixer_filter_output.gain(0, 0.0); // Low pass
        mixer_filter_output.gain(1, 1.0); // Band pass
      }
        
      break;

    case 40: // Lfo rate
      lfo.frequency(LFO_FREQS_HZ[value]);
      break;

    case 41: // Lfo delay
      envelope_lfo_delay.attack(ENV_TIMES_MS[value]);
      break;

    case 42: // Lfo wave shape
      if (value < 21) {
        lfo.begin(WAVEFORM_SINE);
      } else if (value < 42) {
        lfo.begin(WAVEFORM_TRIANGLE);
      } else if (value < 63) {
        lfo.begin(WAVEFORM_SAWTOOTH);
      } else if (value < 84) {
        lfo.begin(WAVEFORM_SAWTOOTH_REVERSE);
      } else if (value < 105) {
        lfo.begin(WAVEFORM_SQUARE);
      } else {
        lfo.begin(WAVEFORM_SAMPLE_HOLD);
      }
      break;

    case 50: { // Amp and filter envelope release times
        uint16_t release_time_ms = ENV_TIMES_MS[value];   // todo - better formula for mapping midi values
        envelope_amp.release(release_time_ms);  
        envelope_filter.release(release_time_ms);
      }
      break;

    case 51: // Filter decay time 
      envelope_filter.decay(3000 * (value / 127.0));  // todo - better formula for mapping midi values
      break;   

    case 60: // Volume
      amp_output.gain(log10(value / 127.0 * 9.0 + 1.0));
      break;
  }
}

void updateFilterMods() {
  uint8_t sum = filter_envelope_depth_cc_value + filter_lfo_depth_cc_value;
  if (sum <= 127) {
    dc_filter_envelope_depth.amplitude(filter_envelope_depth_cc_value / 127.0); // todo - better formula for mapping midi values?
    amp_filter_lfo_depth.gain(filter_lfo_depth_cc_value / 127.0);                   // todo - better formula for mapping midi values?
  } else {
    dc_filter_envelope_depth.amplitude(filter_envelope_depth_cc_value / (float) sum); // todo - better formula for mapping midi values?
    amp_filter_lfo_depth.gain(filter_lfo_depth_cc_value / (float) sum);                   // todo - better formula for mapping midi values?
  }
}

