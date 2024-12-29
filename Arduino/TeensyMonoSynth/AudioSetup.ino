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

  dc_osc_A_pulse_width.amplitude(0.5);

  // Oscillator B
  osc_B.begin(WAVEFORM_BANDLIMIT_SAWTOOTH);
  osc_B.amplitude(0.1);
  osc_B.frequency(440.0);
  osc_B.frequencyModulation(10.0);

  dc_osc_B_pulse_width.amplitude(0.75);

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
  amp_osc_freq_lfo_depth.gain(0.0);
  amp_osc_freq_envelope_depth.gain(0.0);

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

  mixer_filter_mod.gain(0, 1.0); // Lfo
  mixer_filter_mod.gain(1, 1.0); // Env
  mixer_filter_mod.gain(2, 0.0); // Not used
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

  // Envelope
  dc_constant_1.amplitude(1.0);

  envelope.attack(0.0);
  envelope.decay(0.0);
  envelope.sustain(1.0);
  envelope.release(0.0);

  // Output Level
  amp_output.gain(0.7);
}