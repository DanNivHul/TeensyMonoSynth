// GUItool: begin automatically generated code
AudioSynthWaveform       lfo;      //xy=811.9335327148438,1025.9333591461182
AudioEffectEnvelope      envelope_lfo_delay;      //xy=1055.9335021972656,1025.9333543777466
AudioAmplifier           amp_lfo_osc_depth;           //xy=1364.933494567871,459.9336051940918
AudioSynthWaveformDc     dc_filter_envelope_depth;            //xy=1492.3337631225586,1382.667025566101
AudioAmplifier           amp_filter_lfo_depth;           //xy=1699.9334716796875,1267.9333686828613
AudioEffectEnvelope      envelope_filter;      //xy=1702.6003112792969,1382.6003742218018
AudioSynthWaveformDc     dc_osc_freq;            //xy=1731.9338836669922,341.59997749328613
AudioSynthWaveformDc     dc_osc_sub_freq_offset;            //xy=1734.933349609375,794.600175857544
AudioSynthWaveformDc     dc_detune;            //xy=1797.2004470825195,622.0002861022949
AudioMixer4              mixer_filter_mod;         //xy=1983.93359375,1387.9333763122559
AudioMixer4              mixer_osc_A_freq;         //xy=2020.4000396728516,458.5333557128906
AudioMixer4              mixer_osc_B_freq;         //xy=2022.9335174560547,615.6001148223877
AudioMixer4              mixer_osc_sub_freq;         //xy=2027.9336395263672,790.6001853942871
AudioSynthWaveformDc     dc_osc_B_pulse_width;            //xy=2445.933906555176,731.93337059021
AudioSynthWaveformDc     dc_osc_A_pulse_width;            //xy=2462.933906555176,582.2668590545654
AudioSynthWaveformModulated osc_A;   //xy=2651.333786010742,546.3334064483643
AudioSynthWaveformModulated osc_sub;   //xy=2650.933849334717,807.1335220336914
AudioSynthWaveformModulated osc_B;   //xy=2651.6674041748047,697.6668472290039
AudioSynthNoisePink      pink_noise;          //xy=2651.933765411377,916.9334259033203
AudioMixer4              mixer;         //xy=2951.0005493164062,751.3333892822266
AudioFilterStateVariable filter;        //xy=3190.000312805176,946.3333473205566
AudioMixer4              mixer_filter_output;         //xy=3392.600399017334,953.5334510803223
AudioEffectEnvelope      envelope_amp;      //xy=3612.000801086426,952.333438873291
AudioAmplifier           amp_output;           //xy=3791.934024810791,951.9335050582886
AudioOutputI2S           i2s1;           //xy=3951.0009269714355,951.3334379196167
AudioConnection          patchCord1(lfo, envelope_lfo_delay);
AudioConnection          patchCord2(envelope_lfo_delay, amp_filter_lfo_depth);
AudioConnection          patchCord3(envelope_lfo_delay, amp_lfo_osc_depth);
AudioConnection          patchCord4(amp_lfo_osc_depth, 0, mixer_osc_sub_freq, 1);
AudioConnection          patchCord5(amp_lfo_osc_depth, 0, mixer_osc_A_freq, 1);
AudioConnection          patchCord6(amp_lfo_osc_depth, 0, mixer_osc_B_freq, 1);
AudioConnection          patchCord7(dc_filter_envelope_depth, envelope_filter);
AudioConnection          patchCord8(amp_filter_lfo_depth, 0, mixer_filter_mod, 0);
AudioConnection          patchCord9(envelope_filter, 0, mixer_filter_mod, 1);
AudioConnection          patchCord10(dc_osc_freq, 0, mixer_osc_B_freq, 0);
AudioConnection          patchCord11(dc_osc_freq, 0, mixer_osc_sub_freq, 0);
AudioConnection          patchCord12(dc_osc_freq, 0, mixer_osc_A_freq, 0);
AudioConnection          patchCord13(dc_osc_sub_freq_offset, 0, mixer_osc_sub_freq, 2);
AudioConnection          patchCord14(dc_detune, 0, mixer_osc_B_freq, 2);
AudioConnection          patchCord15(mixer_filter_mod, 0, filter, 1);
AudioConnection          patchCord16(mixer_osc_A_freq, 0, osc_A, 0);
AudioConnection          patchCord17(mixer_osc_B_freq, 0, osc_B, 0);
AudioConnection          patchCord18(mixer_osc_sub_freq, 0, osc_sub, 0);
AudioConnection          patchCord19(dc_osc_B_pulse_width, 0, osc_B, 1);
AudioConnection          patchCord20(dc_osc_A_pulse_width, 0, osc_A, 1);
AudioConnection          patchCord21(osc_A, 0, mixer, 0);
AudioConnection          patchCord22(osc_sub, 0, mixer, 2);
AudioConnection          patchCord23(osc_B, 0, mixer, 1);
AudioConnection          patchCord24(pink_noise, 0, mixer, 3);
AudioConnection          patchCord25(mixer, 0, filter, 0);
AudioConnection          patchCord26(filter, 0, mixer_filter_output, 0);
AudioConnection          patchCord27(filter, 1, mixer_filter_output, 1);
AudioConnection          patchCord28(filter, 2, mixer_filter_output, 2);
AudioConnection          patchCord29(mixer_filter_output, envelope_amp);
AudioConnection          patchCord30(envelope_amp, amp_output);
AudioConnection          patchCord31(amp_output, 0, i2s1, 0);
AudioConnection          patchCord32(amp_output, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=3692.0007514953613,1015.3334426879883
// GUItool: end automatically generated code