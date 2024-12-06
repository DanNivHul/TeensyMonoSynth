// ====================================================================================================
// TODO - HIGH PRIORITY
// ====================================================================================================
// todo - glide
// todo - better note on / off. at the moment. store previous notes in buffer and return to them if note off not received
// todo - change square to pulse for Osc A and Osc B and add pulse width ccs for both
// todo - lfo to pulse width. cc for depth
// todo - lfo to osc pitches
// todo - expose full adsr parameters to cc. filter and amp share same settings
// todo - add bandpass option for filter
// todo - set volume to 1


// ====================================================================================================
// TODO - MID PRIORITY
// ====================================================================================================
// todo - add detune to 3rd, 5th, etc?
// todo - pitch bend
// todo - mod wheel to either filter cutoff or lfo depth?
// todo - note velocity to volume. cc for depth
// todo - note velocity to filter cutoff. cc for depth
// todo - envelope to osc pitch
// todo - filter cutoff envelope bipolar. 
// todo - filter cutoff lfo bipolar
// todo - crossfade between osc A and osc B using constant power instead of linear crossfade
// todo - white noise as lfo source
// todo - lfo option where each note on triggers a new random value and sustains it until the next note on 
// todo - send midi over usb to update web programmer
// todo - logical operator distortion - type and crossfade distortion amount


// ====================================================================================================
// TODO - LOW PRIORITY
// ====================================================================================================
// todo - x-mod of oscillators
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

// GUItool: begin automatically generated code
AudioSynthWaveform       lfo;      //xy=623.9333267211914,558.9333109855652
AudioEffectEnvelope      envelope_lfo_delay;      //xy=841.9333648681641,558.9333629608154
AudioSynthWaveformDc     dc_filter_envelope_depth;            //xy=910.333610534668,819.6670064926147
AudioAmplifier           amp_filter_lfo_depth;           //xy=1117.9333190917969,704.933349609375
AudioEffectEnvelope      envelope_filter;      //xy=1120.6001586914062,819.6003551483154
AudioSynthWaveformDc     dc_detune;            //xy=1264.2000350952148,373.00004959106445
AudioMixer4              mixer_filter_mod;         //xy=1401.9334411621094,824.9333572387695
AudioSynthNoisePink      pink_noise;          //xy=1403.933334350586,473.9333381652832
AudioSynthWaveformModulated osc_sub;   //xy=1405.9333267211914,422.1333875656128
AudioSynthWaveformModulated osc_B;   //xy=1409.6668434143066,373.6667060852051
AudioSynthWaveformModulated osc_A;   //xy=1410.3333473205566,322.3332939147949
AudioMixer4              mixer;         //xy=1709.0001182556152,396.33330154418945
AudioFilterStateVariable filter;        //xy=1887.0000228881836,503.33330154418945
AudioEffectEnvelope      envelope_amp;      //xy=2078.000030517578,501.3332710266113
AudioAmplifier           amp_output;           //xy=2257.9332542419434,500.9333372116089
AudioOutputI2S           i2s1;           //xy=2417.000156402588,500.333270072937
AudioConnection          patchCord1(lfo, envelope_lfo_delay);
AudioConnection          patchCord2(envelope_lfo_delay, amp_filter_lfo_depth);
AudioConnection          patchCord3(dc_filter_envelope_depth, envelope_filter);
AudioConnection          patchCord4(amp_filter_lfo_depth, 0, mixer_filter_mod, 0);
AudioConnection          patchCord5(envelope_filter, 0, mixer_filter_mod, 1);
AudioConnection          patchCord6(dc_detune, 0, osc_B, 0);
AudioConnection          patchCord7(mixer_filter_mod, 0, filter, 1);
AudioConnection          patchCord8(pink_noise, 0, mixer, 3);
AudioConnection          patchCord9(osc_sub, 0, mixer, 2);
AudioConnection          patchCord10(osc_B, 0, mixer, 1);
AudioConnection          patchCord11(osc_A, 0, mixer, 0);
AudioConnection          patchCord12(mixer, 0, filter, 0);
AudioConnection          patchCord13(filter, 0, envelope_amp, 0);
AudioConnection          patchCord14(envelope_amp, amp_output);
AudioConnection          patchCord15(amp_output, 0, i2s1, 0);
AudioConnection          patchCord16(amp_output, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=2157.9999809265137,564.3332748413086
// GUItool: end automatically generated code












// CONSTANTS
const uint16_t PROGMEM ENV_TIMES_MS[128] = {1, 2, 4, 6, 9, 14, 20, 26, 33, 41, 49, 58, 67, 78, 89, 99, 111, 124, 136, 150, 164, 178, 192, 209, 224, 241, 258, 276, 295, 314, 333, 353, 374, 395, 418, 440, 464, 489, 513, 539, 565, 592, 621, 650, 680, 710, 742, 774, 808, 843, 878, 915, 952, 991, 1031, 1073, 1114, 1158, 1202, 1250, 1297, 1346, 1396, 1448, 1502, 1558, 1614, 1676, 1735, 1794, 1864, 1923, 1994, 2065, 2136, 2207, 2289, 2360, 2443, 2525, 2620, 2702, 2797, 2891, 2985, 3092, 3186, 3292, 3410, 3516, 3634, 3752, 3882, 4012, 4142, 4272, 4413, 4567, 4708, 4862, 5027, 5180, 5357, 5522, 5699, 5888, 6077, 6278, 6478, 6691, 6903, 7127, 7351, 7587, 7835, 8083, 8343, 8614, 8885, 9169, 9464, 9770, 10077, 10408, 10738, 11080, 11434, 11700};
const uint16_t PROGMEM FILTER_CUTOFF_FREQS_HZ[256] = {20, 21, 22, 23, 24, 26, 27, 28, 29, 31, 32, 33, 34, 35, 36, 38, 39, 40, 41, 43, 44, 46, 47, 49, 50, 52, 53, 55, 57, 59, 61, 63, 65, 68, 70, 73, 76, 78, 81, 84, 87, 91, 94, 98, 102, 106, 110, 114, 119, 123, 128, 133, 138, 144, 149, 155, 161, 167, 174, 181, 187, 195, 202, 210, 218, 226, 234, 243, 252, 261, 271, 281, 291, 301, 312, 323, 334, 346, 358, 370, 383, 395, 409, 422, 436, 451, 465, 480, 496, 512, 528, 544, 561, 578, 596, 614, 633, 652, 671, 691, 711, 732, 753, 774, 796, 818, 841, 865, 888, 913, 937, 962, 988, 1014, 1041, 1068, 1096, 1124, 1152, 1182, 1211, 1242, 1272, 1304, 1335, 1368, 1401, 1434, 1468, 1503, 1538, 1574, 1610, 1647, 1684, 1722, 1761, 1800, 1840, 1881, 1922, 1964, 2006, 2049, 2093, 2137, 2182, 2227, 2274, 2320, 2368, 2416, 2465, 2515, 2565, 2616, 2668, 2720, 2773, 2827, 2881, 2936, 2992, 3049, 3106, 3164, 3223, 3283, 3343, 3404, 3466, 3529, 3592, 3656, 3721, 3787, 3853, 3921, 3989, 4058, 4127, 4198, 4269, 4341, 4414, 4488, 4563, 4638, 4715, 4792, 4870, 4949, 5029, 5109, 5191, 5273, 5357, 5441, 5526, 5612, 5699, 5787, 5876, 5965, 6056, 6147, 6240, 6333, 6427, 6523, 6619, 6716, 6814, 6913, 7013, 7114, 7216, 7319, 7424, 7529, 7635, 7742, 7850, 7959, 8069, 8180, 8292, 8405, 8519, 8634, 8751, 8868, 8986, 9106, 9226, 9348, 9471, 9594, 9719, 9845, 9972, 10100, 10230, 10360, 10491, 10624, 10758, 10893, 11029, 11166, 11304, 11443, 11584, 11726, 11869, 12000};
const float PROGMEM LFO_FREQS_HZ[128] = {0.10000, 0.10140, 0.10561, 0.11263, 0.12245, 0.13508, 0.15051, 0.16875, 0.18980, 0.21365, 0.24031, 0.26977, 0.30204, 0.33712, 0.37500, 0.41569, 0.45918, 0.50548, 0.55459, 0.60651, 0.66122, 0.71875, 0.77908, 0.84222, 0.90816, 0.97691, 1.04847, 1.12283, 1.20000, 1.27997, 1.36276, 1.44834, 1.53673, 1.62793, 1.72194, 1.81875, 1.91837, 2.02079, 2.12602, 2.23406, 2.34490, 2.45855, 2.57500, 2.69426, 2.81633, 2.94120, 3.06888, 3.19936, 3.33265, 3.46875, 3.60765, 3.74936, 3.89388, 4.04120, 4.19133, 4.34426, 4.50000, 4.65855, 4.81990, 4.98406, 5.15102, 5.32079, 5.49337, 5.66875, 5.84694, 6.02793, 6.21173, 6.39834, 6.58776, 6.77997, 6.97500, 7.17283, 7.37347, 7.57691, 7.78316, 7.99222, 8.20408, 8.41875, 8.63622, 8.85651, 9.07959, 9.30548, 9.53418, 9.76569, 10.00000, 10.53542, 12.14170, 14.81882, 18.56679, 23.38561, 29.27528, 36.23580, 44.26717, 53.36939, 63.54246, 74.78637, 87.10114, 100.48675, 114.94321, 130.47052, 147.06869, 164.73770, 183.47756, 203.28826, 224.16982, 246.12223, 269.14548, 293.23959, 318.40454, 344.64035, 371.94700, 400.32450, 429.77285, 460.29205, 491.88210, 524.54300, 558.27474, 593.07734, 628.95078, 665.89508, 703.91022, 742.99621, 783.15306, 824.38075, 866.67929, 910.04867, 954.48891, 1000.00000};
const float noteFreqs[128] = {8.176, 8.662, 9.177, 9.723, 10.301, 10.913, 11.562, 12.25, 12.978, 13.75, 14.568, 15.434, 16.352, 17.324, 18.354, 19.445, 20.602, 21.827, 23.125, 24.5, 25.957, 27.5, 29.135, 30.868, 32.703, 34.648, 36.708, 38.891, 41.203, 43.654, 46.249, 48.999, 51.913, 55, 58.27, 61.735, 65.406, 69.296, 73.416, 77.782, 82.407, 87.307, 92.499, 97.999, 103.826, 110, 116.541, 123.471, 130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998, 207.652, 220, 233.082, 246.942, 261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440, 466.164, 493.883, 523.251, 554.365, 587.33, 622.254, 659.255, 698.456, 739.989, 783.991, 830.609, 880, 932.328, 987.767, 1046.502, 1108.731, 1174.659, 1244.508, 1318.51, 1396.913, 1479.978, 1567.982, 1661.219, 1760, 1864.655, 1975.533, 2093.005, 2217.461, 2349.318, 2489.016, 2637.02, 2793.826, 2959.955, 3135.963, 3322.438, 3520, 3729.31, 3951.066, 4186.009, 4434.922, 4698.636, 4978.032, 5274.041, 5587.652, 5919.911, 6271.927, 6644.875, 7040, 7458.62, 7902.133, 8372.018, 8869.844, 9397.273, 9956.063, 10548.08, 11175.3, 11839.82, 12543.85};

// GLOBALS
uint8_t filter_envelope_depth_cc_value = 0;
uint8_t filter_lfo_depth_cc_value = 0;

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

  // OSCILLATOR A
  osc_A.begin(WAVEFORM_BANDLIMIT_SAWTOOTH);
  osc_A.amplitude(0.1);
  osc_A.frequency(0.0);
  osc_A.frequencyModulation(10.0);

  // OSCILLATOR B
  osc_B.begin(WAVEFORM_BANDLIMIT_SAWTOOTH);
  osc_B.amplitude(0.1);
  osc_B.frequency(0.0);
  osc_B.frequencyModulation(10.0);

  dc_detune.amplitude(0.001);

  // OSCILLATOR SUB
  osc_sub.begin(WAVEFORM_SINE);
  osc_sub.amplitude(0.2);
  osc_sub.frequency(0.0);
  osc_sub.frequencyModulation(10.0);

  // NOISE GENERATOR
  pink_noise.amplitude(0.1);

  //MIXER
  mixer.gain(0, 0.1); // Osc A
  mixer.gain(1, 0.1); // Osc B
  mixer.gain(2, 0.2); // Osc Sub
  mixer.gain(3, 0.1); // Noise

  //FILTER
  filter.frequency(12000.0);
  filter.resonance(1.0);
  filter.octaveControl(0.0);

  //FILTER ENV
  envelope_filter.attack(1.0);
  envelope_filter.decay(500.0);
  envelope_filter.sustain(0.0);
  envelope_filter.release(0.0);

  //FILTER MOD
  dc_filter_envelope_depth.amplitude(0.0);
  amp_filter_lfo_depth.gain(0.0);

  mixer_filter_mod.gain(0, 1.0); // Lfo
  mixer_filter_mod.gain(1, 1.0); // Env
  mixer_filter_mod.gain(2, 0.0); // Not used
  mixer_filter_mod.gain(3, 0.0); // Not used

  //AMP ENV
  envelope_amp.attack(1.0);
  envelope_amp.decay(0.0);
  envelope_amp.sustain(1.0);
  envelope_amp.release(500.0);

  //LFO
  lfo.begin(WAVEFORM_TRIANGLE);
  lfo.amplitude(1.0);
  lfo.frequency(0.1);
  lfo.offset(0.5);

  envelope_lfo_delay.attack(0.0);
  envelope_lfo_delay.decay(0.0);
  envelope_lfo_delay.sustain(1.0);
  envelope_lfo_delay.release(0.0);
  envelope_lfo_delay.releaseNoteOn(0.0);

  //OUTPUT LEVEL
  amp_output.gain(0.7);


  Serial.println("Hello World");
}


void loop() {
  usbMIDI.read();
  MIDI.read();
}

void myNoteOn(byte channel, byte note, byte velocity) {
  Serial.println("Note on");
  
  AudioNoInterrupts();  // Disable the audio library update interrupt. This allows more than 1 object's settings to be changed simultaneously.

  osc_A.frequency(noteFreqs[note]);
  osc_B.frequency(noteFreqs[note]);
  osc_sub.frequency(noteFreqs[note] / 2.0);
  envelope_amp.noteOn();
  envelope_filter.noteOn();
  envelope_lfo_delay.noteOn();
  
  AudioInterrupts();  // Enable the audio library update interrupt. Any settings changed will all take effect at the same time.
}

void myNoteOff(byte channel, byte note, byte velocity) {
  Serial.println("Note off");

  AudioNoInterrupts();  // Disable the audio library update interrupt. This allows more than 1 object's settings to be changed simultaneously.

  envelope_amp.noteOff();
  envelope_filter.noteOff();

  AudioInterrupts();  // Enable the audio library update interrupt. Any settings changed will all take effect at the same time.
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
        float detune_level = value / 127.0 * 0.008 - 0.004; // gives a swing of just less than -0.5 semitone to +0.5 semitone
        dc_detune.amplitude(detune_level);
      }
      break;

    case 20: { // Mix between Osc A and Osc B
        float osc_B_level = value / 127.0 * 0.2;
        float osc_A_level = 0.2 - osc_B_level;
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

