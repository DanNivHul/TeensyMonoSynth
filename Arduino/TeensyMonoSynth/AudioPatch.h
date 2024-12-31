// GUItool: begin automatically generated code
AudioSynthWaveform       lfo;            //xy=895.3999710083008,1575.666711807251
AudioSynthWaveformDc     dc_pitch_bend;            //xy=1052.406349182129,950.8251438140869
AudioSynthWaveformDc     dc_osc_freq;    //xy=1082.3999481201172,801.6667232513428
AudioEffectEnvelope      envelope_lfo_delay; //xy=1139.3999710083008,1575.666711807251
AudioAmplifier           amp_pitch_lfo_depth; //xy=1218.3999404907227,1059.66672706604
AudioSynthWaveformDc     dc_pitch_env;            //xy=1285.406337738037,1192.8250579833984
AudioSynthWaveformDc     dc_note_velocity;            //xy=1501.8064193725586,2136.8247394561768
AudioSynthWaveformDc     dc_filter_envelope_depth; //xy=1576.3999710083008,1932.666711807251
AudioMixer4              mixer_osc_common_freq;         //xy=1609.4062957763672,981.8251132965088
AudioSynthWaveformDc     dc_osc_sub_freq_offset; //xy=1691.3999481201172,1445.6668577194214
AudioAmplifier           amp_filter_lfo_depth; //xy=1783.3999710083008,1817.666711807251
AudioAmplifier           amp_filter_note_velocity_depth;           //xy=1785.8067016601562,2041.825044631958
AudioEffectEnvelope      envelope_filter; //xy=1786.3999710083008,1932.666711807251
AudioSynthWaveformDc     dc_constant_1;            //xy=1933.8065490722656,2484.824866294861
AudioMixer4              mixer_osc_sub_freq; //xy=1971.3999481201172,1454.666856765747
AudioSynthWaveformDc     dc_detune;      //xy=2047.3999481201172,1208.6667051315308
AudioMixer4              mixer_filter_mod; //xy=2067.399971008301,1937.666711807251
AudioMixer4              mixer_invert_1;         //xy=2075.8060760498047,2223.824863433838
AudioMixer4              mixer_osc_B_freq; //xy=2336.399833679199,1212.666706085205
AudioMixer4              mixer_osc_A_freq;         //xy=2490.806083679199,1002.8251495361328
AudioAmplifier           amp_volume_note_velocity_depth;           //xy=2555.80606842041,2088.824864387512
AudioSynthWaveformModulated osc_A;          //xy=2726.3998374938965,1072.6667041778564
AudioSynthWaveformModulated osc_sub;        //xy=2734.399971008301,1357.666711807251
AudioSynthWaveformModulated osc_B;          //xy=2735.399971008301,1247.666711807251
AudioSynthNoisePink      pink_noise;     //xy=2735.399971008301,1466.666711807251
AudioMixer4              mixer;          //xy=3035.399971008301,1301.666711807251
AudioMixer4              mixer_invert_2;         //xy=3120.806327819824,2063.8248596191406
AudioFilterStateVariable filter;         //xy=3274.399971008301,1496.666711807251
AudioMixer4              mixer_filter_output; //xy=3476.399971008301,1503.666711807251
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
AudioConnection          patchCord8(dc_note_velocity, amp_filter_note_velocity_depth);
AudioConnection          patchCord9(dc_note_velocity, 0, mixer_invert_1, 0);
AudioConnection          patchCord10(dc_filter_envelope_depth, envelope_filter);
AudioConnection          patchCord11(mixer_osc_common_freq, 0, mixer_osc_B_freq, 0);
AudioConnection          patchCord12(mixer_osc_common_freq, 0, mixer_osc_sub_freq, 0);
AudioConnection          patchCord13(mixer_osc_common_freq, 0, mixer_osc_A_freq, 0);
AudioConnection          patchCord14(dc_osc_sub_freq_offset, 0, mixer_osc_sub_freq, 1);
AudioConnection          patchCord15(amp_filter_lfo_depth, 0, mixer_filter_mod, 0);
AudioConnection          patchCord16(amp_filter_note_velocity_depth, 0, mixer_filter_mod, 2);
AudioConnection          patchCord17(envelope_filter, 0, mixer_filter_mod, 1);
AudioConnection          patchCord18(dc_constant_1, 0, mixer_invert_1, 1);
AudioConnection          patchCord19(dc_constant_1, 0, mixer_invert_2, 1);
AudioConnection          patchCord20(mixer_osc_sub_freq, 0, osc_sub, 0);
AudioConnection          patchCord21(dc_detune, 0, mixer_osc_B_freq, 1);
AudioConnection          patchCord22(mixer_filter_mod, 0, filter, 1);
AudioConnection          patchCord23(mixer_invert_1, amp_volume_note_velocity_depth);
AudioConnection          patchCord24(mixer_osc_B_freq, 0, osc_B, 0);
AudioConnection          patchCord25(mixer_osc_A_freq, 0, osc_A, 0);
AudioConnection          patchCord26(amp_volume_note_velocity_depth, 0, mixer_invert_2, 0);
AudioConnection          patchCord27(osc_A, 0, mixer, 0);
AudioConnection          patchCord28(osc_sub, 0, mixer, 2);
AudioConnection          patchCord29(osc_B, 0, mixer, 1);
AudioConnection          patchCord30(osc_B, 0, mixer_osc_A_freq, 1);
AudioConnection          patchCord31(pink_noise, 0, mixer, 3);
AudioConnection          patchCord32(mixer, 0, filter, 0);
AudioConnection          patchCord33(mixer_invert_2, 0, multiply_1, 1);
AudioConnection          patchCord34(filter, 0, mixer_filter_output, 0);
AudioConnection          patchCord35(filter, 1, mixer_filter_output, 1);
AudioConnection          patchCord36(filter, 2, mixer_filter_output, 2);
AudioConnection          patchCord37(mixer_filter_output, envelope_amp);
AudioConnection          patchCord38(envelope_amp, 0, multiply_1, 0);
AudioConnection          patchCord39(multiply_1, amp_output);
AudioConnection          patchCord40(amp_output, 0, i2s1, 0);
AudioConnection          patchCord41(amp_output, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=4247.3999671936035,1597.6668348312378
// GUItool: end automatically generated code