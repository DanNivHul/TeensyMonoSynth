void myControlChange(byte channel, byte control, byte value) {
  // Serial.print("Channel: ");
  // Serial.print(channel);
  // Serial.print(", cc: ");
  // Serial.print(control);
  // Serial.print(", value: ");
  // Serial.println(value);

  switch (control) {

    case 1: { // Mod Wheel
        // Update lfo amplitude
        // Update offset by the same amount to keep lfo range from 0 to 2 * amplitude
        float amplitude = value / 127.0 * MAX_LFO_AMPLITUDE;
        lfo_1.amplitude(amplitude);
        lfo_1.offset(amplitude);
        lfo_2.amplitude(amplitude);
        lfo_2.offset(amplitude);
      }
      break;

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

    case 13: { // Osc B FM Osc A
        mixer_osc_A_freq.gain(1, POWER[value] * MAX_CROSS_MODULATION_DEPTH);
      }
      break;

    case 14: { // Glide - enable / disable
        is_glide_enabled = value < 64;
      }
      break;

    case 15: { // Legato - enable / disable
        is_legato_enabled = value < 64;
      }
      break;

    case 16: { // Osc lfo depth
        amp_pitch_lfo_1_depth.gain(POWER[value] * MAX_OSC_LFO_AMPLITUDE);
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
      filter_envelope_depth = value / 127.0;
      updateFilterMods();
      break;

    case 33: // Filter lfo 1 depth 
      filter_lfo_1_depth = value / 127.0;
      updateFilterMods();
      break;

    case 34: // Filter velocity depth 
      filter_velocity_depth = value / 127.0;
      updateFilterMods();
      break;

    case 35: // Filter type - low pass / band pass 
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

    case 36: // Filter lfo 2 depth 
      filter_lfo_2_depth = value / 127.0;
      updateFilterMods();
      break;

    case 40: // Lfo 1 - Rate
      lfo_1.frequency(LFO_FREQS_HZ[value]);
      break;

    case 41: // Lfo 1 - Delay
      envelope_lfo_1_delay.attack(ENV_TIMES_MS[value]);
      break;

    case 42: // Lfo 1 - Wave Shape
      if (value < 21) {
        lfo_1.begin(WAVEFORM_SINE);
      } else if (value < 42) {
        lfo_1.begin(WAVEFORM_TRIANGLE);
      } else if (value < 63) {
        lfo_1.begin(WAVEFORM_SAWTOOTH);
      } else if (value < 84) {
        lfo_1.begin(WAVEFORM_SAWTOOTH_REVERSE);
      } else if (value < 105) {
        lfo_1.begin(WAVEFORM_SQUARE);
      } else {
        lfo_1.begin(WAVEFORM_SAMPLE_HOLD);
      }
      break;

    case 43: // Lfo 2 - Rate
      lfo_2.frequency(LFO_FREQS_HZ[value]);
      break;

    case 44: // Lfo 2 - Lfo 1 fm
      amp_lfo_2_to_lfo_1_mod_depth.gain(POWER[value] * MAX_LFO_2_TO_LFO_1_MOD_DEPTH);
      break;

    case 45: // Lfo 2 - Wave Shape
      if (value < 21) {
        lfo_2.begin(WAVEFORM_SINE);
      } else if (value < 42) {
        lfo_2.begin(WAVEFORM_TRIANGLE);
      } else if (value < 63) {
        lfo_2.begin(WAVEFORM_SAWTOOTH);
      } else if (value < 84) {
        lfo_2.begin(WAVEFORM_SAWTOOTH_REVERSE);
      } else if (value < 105) {
        lfo_2.begin(WAVEFORM_SQUARE);
      } else {
        lfo_2.begin(WAVEFORM_SAMPLE_HOLD);
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

    case 61: // Note velocity to volume depth
      amp_volume_note_velocity_depth.gain(log10(value / 127.0 * 9.0 + 1.0));
      break;
  }
}

void updateFilterMods() {
  float sum = filter_envelope_depth + filter_lfo_1_depth + filter_lfo_2_depth + filter_velocity_depth;
  if (sum <= 1.0) {
    dc_filter_envelope_depth.amplitude(filter_envelope_depth); 
    amp_filter_lfo_1_depth.gain(filter_lfo_1_depth);               
    amp_filter_lfo_2_depth.gain(filter_lfo_2_depth);               
    amp_filter_note_velocity_depth.gain(filter_velocity_depth);
  } else {
    dc_filter_envelope_depth.amplitude(filter_envelope_depth / sum); 
    amp_filter_lfo_1_depth.gain(filter_lfo_1_depth / sum);   
    amp_filter_lfo_2_depth.gain(filter_lfo_2_depth / sum);                           
    amp_filter_note_velocity_depth.gain(filter_velocity_depth / sum);
  }
}

void updateDetune() {
  dc_detune.amplitude(detune_amount + semitone_offset);
}