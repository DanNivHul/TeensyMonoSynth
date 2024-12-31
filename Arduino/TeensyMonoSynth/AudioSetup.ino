void setupAudio() {
  AudioMemory(60);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.7);

  // Volt Per Octave
  dc_osc_freq.amplitude(0.0);

  // Pitch bend
  dc_pitch_bend.amplitude(0.0);

  // Common oscillator frequency
  mixer_osc_common_freq.gain(0, 1.0);  // Note frequency
  mixer_osc_common_freq.gain(1, 1.0);  // Pitch bend
  mixer_osc_common_freq.gain(2, 1.0);  // Lfo
  mixer_osc_common_freq.gain(3, 1.0);  // Envelope

  // Oscillator A
  osc_A.begin(WAVEFORM_BANDLIMIT_SAWTOOTH);
  osc_A.amplitude(0.1);
  osc_A.frequency(440.0);
  osc_A.frequencyModulation(10.0);

  mixer_osc_A_freq.gain(0, 1.0);  // Common frequency - note, pitch bend, etc.
  mixer_osc_A_freq.gain(1, 0.0);  // Osc B FM Osc A
  mixer_osc_A_freq.gain(2, 0.0);  // Not used
  mixer_osc_A_freq.gain(3, 0.0);  // Not used

  // Oscillator B
  osc_B.begin(WAVEFORM_BANDLIMIT_SAWTOOTH);
  osc_B.amplitude(0.1);
  osc_B.frequency(440.0);
  osc_B.frequencyModulation(10.0);

  dc_detune.amplitude(detune_amount);

  mixer_osc_B_freq.gain(0, 1.0);  // Common frequency - note, pitch bend, etc.
  mixer_osc_B_freq.gain(1, 1.0);  // Detune
  mixer_osc_B_freq.gain(2, 0.0);  // Not used
  mixer_osc_B_freq.gain(3, 0.0);  // Not used

  // Oscillator Sub
  osc_sub.begin(WAVEFORM_SINE);
  osc_sub.amplitude(0.2);
  osc_sub.frequency(440.0);
  osc_sub.frequencyModulation(10.0);

  dc_osc_sub_freq_offset.amplitude(-0.1);

  mixer_osc_sub_freq.gain(0, 1.0);  // Common frequency - note, pitch bend, etc.
  mixer_osc_sub_freq.gain(1, 1.0);  // Offset (i.e. one octave down)
  mixer_osc_sub_freq.gain(2, 0.0);  // Not used
  mixer_osc_sub_freq.gain(3, 0.0);  // Not used

  // Oscillator Modulation
  amp_pitch_lfo_depth.gain(0.0);
  dc_pitch_env.amplitude(0.0);

  // Noise Generator
  pink_noise.amplitude(0.1);

  // Mixer
  mixer.gain(0, 0.707 * MAX_OSC_LEVEL); // Osc A
  mixer.gain(1, 0.707 * MAX_OSC_LEVEL); // Osc B
  mixer.gain(2, 0.2); // Osc Sub
  mixer.gain(3, 0.1); // Noise

  // Filter
  filter.frequency(12000.0);
  filter.resonance(1.0);
  filter.octaveControl(0.0);

  // Filter Env
  envelope_filter.attack(1.0);
  envelope_filter.decay(500.0);
  envelope_filter.sustain(0.0);
  envelope_filter.release(0.0);

  // Filter Type - Low Pass / Band Pass
  mixer_filter_output.gain(0, 1.0); // Low pass
  mixer_filter_output.gain(1, 0.0); // Band pass
  mixer_filter_output.gain(2, 0.0); // Not used
  mixer_filter_output.gain(3, 0.0); // Not used

  // Filter Modulation
  dc_filter_envelope_depth.amplitude(0.0);
  amp_filter_lfo_depth.gain(0.0);
  amp_filter_note_velocity_depth.gain(filter_velocity_depth);

  mixer_filter_mod.gain(0, 1.0); // Lfo
  mixer_filter_mod.gain(1, 1.0); // Env
  mixer_filter_mod.gain(2, 1.0); // Note velocity
  mixer_filter_mod.gain(3, 0.0); // Not used

  // Amplitude Envelope
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

  // Note Velocity to Volume Mod
  amp_volume_note_velocity_depth.gain(0.25);

  mixer_invert_1.gain(0, -1.0); // Note Velocity
  mixer_invert_1.gain(1,  1.0); // Constant 1 Volt
  mixer_invert_1.gain(2,  0.0); // Not used
  mixer_invert_1.gain(3,  0.0); // Not used


  mixer_invert_2.gain(0, -1.0); // Note Velocity Depth
  mixer_invert_2.gain(1,  1.0); // Constant 1 Volt
  mixer_invert_2.gain(2,  0.0); // Not used
  mixer_invert_2.gain(3,  0.0); // Not used

  // Output Level
  amp_output.gain(0.7);

  // Util
  dc_constant_1.amplitude(1.0);
}