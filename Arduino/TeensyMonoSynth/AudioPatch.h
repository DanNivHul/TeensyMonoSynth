// GUItool: begin automatically generated code
AudioSynthWaveform       lfo;            //xy=895.3999710083008,1575.666711807251
AudioSynthWaveformDc     dc_pitch_bend;            //xy=1052.406349182129,950.8251438140869
AudioSynthWaveformDc     dc_osc_freq;    //xy=1082.3999481201172,801.6667232513428
AudioEffectEnvelope      envelope_lfo_delay; //xy=1139.3999710083008,1575.666711807251
AudioAmplifier           amp_pitch_lfo_depth; //xy=1218.3999404907227,1059.66672706604
AudioSynthWaveformDc     dc_pitch_env;            //xy=1285.406337738037,1192.8250579833984
AudioSynthWaveformDc     dc_filter_envelope_depth; //xy=1576.3999710083008,1932.666711807251
AudioMixer4              mixer_osc_common_freq;         //xy=1609.4062957763672,981.8251132965088
AudioSynthWaveformDc     dc_osc_sub_freq_offset; //xy=1691.3999481201172,1445.6668577194214
AudioAmplifier           amp_filter_lfo_depth; //xy=1783.3999710083008,1817.666711807251
AudioEffectEnvelope      envelope_filter; //xy=1786.3999710083008,1932.666711807251
AudioMixer4              mixer_osc_sub_freq; //xy=1971.3999481201172,1454.666856765747
AudioSynthWaveformDc     dc_detune;      //xy=2018.3999557495117,1158.6667308807373
AudioMixer4              mixer_filter_mod; //xy=2067.399971008301,1937.666711807251
AudioMixer4              mixer_osc_B_freq; //xy=2261.3999557495117,1164.6667308807373
AudioSynthWaveformModulated osc_A;          //xy=2735.399971008301,1096.666711807251
AudioSynthWaveformModulated osc_sub;        //xy=2734.399971008301,1357.666711807251
AudioSynthWaveformModulated osc_B;          //xy=2735.399971008301,1247.666711807251
AudioSynthNoisePink      pink_noise;     //xy=2735.399971008301,1466.666711807251
AudioMixer4              mixer;          //xy=3035.399971008301,1301.666711807251
AudioFilterStateVariable filter;         //xy=3274.399971008301,1496.666711807251
AudioMixer4              mixer_filter_output; //xy=3476.399971008301,1503.666711807251
AudioSynthWaveformDc     dc_note_velocity;            //xy=3690.406219482422,1596.8249969482422
AudioEffectEnvelope      envelope_amp;   //xy=3696.399971008301,1502.666711807251
AudioEffectMultiply      multiply_1;      //xy=3910.4063110351562,1502.825159072876
AudioAmplifier           amp_output;     //xy=4101.3999671936035,1500.6667108535767
AudioOutputI2S           i2s1;           //xy=4286.399971008301,1496.6667108535767
AudioConnection          patchCord1(lfo, envelope_lfo_delay);
AudioConnection          patchCord2(dc_pitch_bend, 0, mixer_osc_common_freq, 1);
AudioConnection          patchCord3(dc_osc_freq, 0, mixer_osc_common_freq, 0);
AudioConnection          patchCord4(envelope_lfo_delay, amp_filter_lfo_depth);
AudioConnection          patchCord5(envelope_lfo_delay, amp_pitch_lfo_depth);
AudioConnection          patchCord6(amp_pitch_lfo_depth, 0, mixer_osc_common_freq, 2);
AudioConnection          patchCord7(dc_pitch_env, 0, mixer_osc_common_freq, 3);
AudioConnection          patchCord8(dc_filter_envelope_depth, envelope_filter);
AudioConnection          patchCord9(mixer_osc_common_freq, 0, mixer_osc_B_freq, 0);
AudioConnection          patchCord10(mixer_osc_common_freq, 0, mixer_osc_sub_freq, 0);
AudioConnection          patchCord11(mixer_osc_common_freq, 0, osc_A, 0);
AudioConnection          patchCord12(dc_osc_sub_freq_offset, 0, mixer_osc_sub_freq, 1);
AudioConnection          patchCord13(amp_filter_lfo_depth, 0, mixer_filter_mod, 0);
AudioConnection          patchCord14(envelope_filter, 0, mixer_filter_mod, 1);
AudioConnection          patchCord15(mixer_osc_sub_freq, 0, osc_sub, 0);
AudioConnection          patchCord16(dc_detune, 0, mixer_osc_B_freq, 1);
AudioConnection          patchCord17(mixer_filter_mod, 0, filter, 1);
AudioConnection          patchCord18(mixer_osc_B_freq, 0, osc_B, 0);
AudioConnection          patchCord19(osc_A, 0, mixer, 0);
AudioConnection          patchCord20(osc_sub, 0, mixer, 2);
AudioConnection          patchCord21(osc_B, 0, mixer, 1);
AudioConnection          patchCord22(pink_noise, 0, mixer, 3);
AudioConnection          patchCord23(mixer, 0, filter, 0);
AudioConnection          patchCord24(filter, 0, mixer_filter_output, 0);
AudioConnection          patchCord25(filter, 1, mixer_filter_output, 1);
AudioConnection          patchCord26(filter, 2, mixer_filter_output, 2);
AudioConnection          patchCord27(mixer_filter_output, envelope_amp);
AudioConnection          patchCord28(dc_note_velocity, 0, multiply_1, 1);
AudioConnection          patchCord29(envelope_amp, 0, multiply_1, 0);
AudioConnection          patchCord30(multiply_1, amp_output);
AudioConnection          patchCord31(amp_output, 0, i2s1, 0);
AudioConnection          patchCord32(amp_output, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=4247.3999671936035,1597.6668348312378
// GUItool: end automatically generated code