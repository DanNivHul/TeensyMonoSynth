// GUItool: begin automatically generated code
AudioSynthWaveformDc     dc_constant_1;            //xy=1295.4062118530273,1328.8249111175537
AudioEffectEnvelope      envelope;      //xy=1459.4062118530273,1329.8249111175537
AudioSynthWaveform       lfo;            //xy=1599.39990234375,1603.6665649414062
AudioSynthWaveformDc     dc_pitch_bend;            //xy=1756.4062805175781,978.8249969482422
AudioSynthWaveformDc     dc_osc_freq;    //xy=1786.3998794555664,829.666576385498
AudioEffectEnvelope      envelope_lfo_delay; //xy=1843.39990234375,1603.6665649414062
AudioAmplifier           amp_osc_freq_lfo_depth; //xy=1922.3998718261719,1087.6665802001953
AudioAmplifier           amp_osc_freq_envelope_depth;           //xy=2008.4062194824219,1227.824909210205
AudioSynthWaveformDc     dc_filter_envelope_depth; //xy=2280.39990234375,1960.6665649414062
AudioMixer4              mixer_osc_common_freq;         //xy=2313.4062271118164,1009.8249664306641
AudioSynthWaveformDc     dc_osc_sub_freq_offset; //xy=2395.3998794555664,1473.6667108535767
AudioAmplifier           amp_filter_lfo_depth; //xy=2487.39990234375,1845.6665649414062
AudioEffectEnvelope      envelope_filter; //xy=2490.39990234375,1960.6665649414062
AudioMixer4              mixer_osc_sub_freq; //xy=2675.3998794555664,1482.6667098999023
AudioSynthWaveformDc     dc_detune;      //xy=2722.399887084961,1186.6665840148926
AudioMixer4              mixer_filter_mod; //xy=2771.39990234375,1965.6665649414062
AudioMixer4              mixer_osc_B_freq; //xy=2965.399887084961,1192.6665840148926
AudioSynthWaveformDc     dc_osc_B_pulse_width; //xy=3233.39990234375,1309.6665649414062
AudioSynthWaveformDc     dc_osc_A_pulse_width; //xy=3250.39990234375,1160.6665649414062
AudioSynthWaveformModulated osc_A;          //xy=3439.39990234375,1124.6665649414062
AudioSynthWaveformModulated osc_sub;        //xy=3438.39990234375,1385.6665649414062
AudioSynthWaveformModulated osc_B;          //xy=3439.39990234375,1275.6665649414062
AudioSynthNoisePink      pink_noise;     //xy=3439.39990234375,1494.6665649414062
AudioMixer4              mixer;          //xy=3739.39990234375,1329.6665649414062
AudioFilterStateVariable filter;         //xy=3978.39990234375,1524.6665649414062
AudioMixer4              mixer_filter_output; //xy=4180.39990234375,1531.6665649414062
AudioEffectEnvelope      envelope_amp;   //xy=4400.39990234375,1530.6665649414062
AudioAmplifier           amp_output;     //xy=4579.39990234375,1529.6665649414062
AudioOutputI2S           i2s1;           //xy=4739.39990234375,1529.6665649414062
AudioConnection          patchCord1(dc_constant_1, envelope);
AudioConnection          patchCord2(envelope, amp_osc_freq_envelope_depth);
AudioConnection          patchCord3(lfo, envelope_lfo_delay);
AudioConnection          patchCord4(dc_pitch_bend, 0, mixer_osc_common_freq, 1);
AudioConnection          patchCord5(dc_osc_freq, 0, mixer_osc_common_freq, 0);
AudioConnection          patchCord6(envelope_lfo_delay, amp_filter_lfo_depth);
AudioConnection          patchCord7(envelope_lfo_delay, amp_osc_freq_lfo_depth);
AudioConnection          patchCord8(amp_osc_freq_lfo_depth, 0, mixer_osc_common_freq, 2);
AudioConnection          patchCord9(amp_osc_freq_envelope_depth, 0, mixer_osc_common_freq, 3);
AudioConnection          patchCord10(dc_filter_envelope_depth, envelope_filter);
AudioConnection          patchCord11(mixer_osc_common_freq, 0, mixer_osc_B_freq, 0);
AudioConnection          patchCord12(mixer_osc_common_freq, 0, mixer_osc_sub_freq, 0);
AudioConnection          patchCord13(mixer_osc_common_freq, 0, osc_A, 0);
AudioConnection          patchCord14(dc_osc_sub_freq_offset, 0, mixer_osc_sub_freq, 1);
AudioConnection          patchCord15(amp_filter_lfo_depth, 0, mixer_filter_mod, 0);
AudioConnection          patchCord16(envelope_filter, 0, mixer_filter_mod, 1);
AudioConnection          patchCord17(mixer_osc_sub_freq, 0, osc_sub, 0);
AudioConnection          patchCord18(dc_detune, 0, mixer_osc_B_freq, 1);
AudioConnection          patchCord19(mixer_filter_mod, 0, filter, 1);
AudioConnection          patchCord20(mixer_osc_B_freq, 0, osc_B, 0);
AudioConnection          patchCord21(dc_osc_B_pulse_width, 0, osc_B, 1);
AudioConnection          patchCord22(dc_osc_A_pulse_width, 0, osc_A, 1);
AudioConnection          patchCord23(osc_A, 0, mixer, 0);
AudioConnection          patchCord24(osc_sub, 0, mixer, 2);
AudioConnection          patchCord25(osc_B, 0, mixer, 1);
AudioConnection          patchCord26(pink_noise, 0, mixer, 3);
AudioConnection          patchCord27(mixer, 0, filter, 0);
AudioConnection          patchCord28(filter, 0, mixer_filter_output, 0);
AudioConnection          patchCord29(filter, 1, mixer_filter_output, 1);
AudioConnection          patchCord30(filter, 2, mixer_filter_output, 2);
AudioConnection          patchCord31(mixer_filter_output, envelope_amp);
AudioConnection          patchCord32(envelope_amp, amp_output);
AudioConnection          patchCord33(amp_output, 0, i2s1, 0);
AudioConnection          patchCord34(amp_output, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=4480.39990234375,1593.6665649414062
// GUItool: end automatically generated code