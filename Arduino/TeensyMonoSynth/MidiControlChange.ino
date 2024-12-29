void myControlChange(byte channel, byte control, byte value) {
  // Serial.print("Channel: ");
  // Serial.print(channel);
  // Serial.print(", cc: ");
  // Serial.print(control);
  // Serial.print(", value: ");
  // Serial.println(value);

  switch (control) {

    case 10: { // Osc Waveshapes
        if (value < 43) {
          osc_A.begin(WAVEFORM_BANDLIMIT_SAWTOOTH);
          osc_B.begin(WAVEFORM_BANDLIMIT_SAWTOOTH);
        } else if (value < 87) {
          osc_A.begin(WAVEFORM_BANDLIMIT_SAWTOOTH);
          osc_B.begin(WAVEFORM_BANDLIMIT_SQUARE);
        } else {
          osc_A.begin(WAVEFORM_BANDLIMIT_PULSE);
          osc_B.begin(WAVEFORM_BANDLIMIT_SQUARE);
        }
      } 
      break;

    case 11: { // Osc B - Detune
        detune_amount = value / 127.0 * 0.01 - 0.005; // gives a range from a little below -0.5 semitone to a little above +0.5 semitone
        updateDetune();
      }
      break;

    case 12: { // Osc B semitone
        // Gives a range from -12 to +12 semitones
        int8_t num_semitones;
        if (value < 60) {
            num_semitones = value / 5 - 12;    
        } else if (value > 67) { 
            num_semitones = (value - 3) / 5 - 12;
        } else {
            num_semitones = 0;
        }
        semitone_offset = num_semitones * 0.0083333333; // One semitone in volts
        updateDetune();
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
        amp_osc_freq_lfo_depth.gain(POWER[value] * MAX_OSC_LFO_AMPLITUDE);
      }
      break;

    case 17: { // Pitch envelope depth
        if (value >= 62 && value <= 65) {
          pitch_envelope_depth = 0.0;
        } else {
          pitch_envelope_depth = ((value / 127.0 * 2.0) - 1.0) * MAX_PITCH_ENVELOPE_DEPTH;
        }
      }
      break;

    case 18: { // Pitch envelope decay time
        pitch_envelope_decay_time_ms = value;
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

void updateDetune() {
  dc_detune.amplitude(detune_amount + semitone_offset);
}