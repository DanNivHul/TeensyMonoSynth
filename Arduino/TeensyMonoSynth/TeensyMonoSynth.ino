// ====================================================================================================
// TODO - HIGH PRIORITY
// ====================================================================================================
// todo - change square to pulse for Osc A and Osc B and add pulse width ccs for both (on second thought, if you have lfo and envelope to pulse width, do you need manual set of pulse width? I guess helpful for testing?)
// todo - lfo to pulse width. cc for depth
// todo - envelope to pulse width. cc for depth
// todo - lfo to osc pitches
// todo - expose full adsr parameters to cc. filter and amp share same settings
// todo - add bandpass option for filter
// todo - set volume to 1
// todo - sub waveform select (square or 25% pulse?)
// todo - option for legato mode (retrigger envelopes vs don't)
// done - better note on / off. at the moment. store previous notes in buffer and return to them if note off not received
// done - glide


// ====================================================================================================
// TODO - MID PRIORITY
// ====================================================================================================
// todo - finalise glide times. or alternatively have a constant glide time and either turn it on or off
// todo - add detune to 3rd, 5th, etc?
// todo - pitch bend
// todo - mod wheel to either filter cutoff or lfo depth?
// todo - note velocity to volume. cc for depth
// todo - note velocity to filter cutoff. cc for depth
// todo - envelope to osc pitch
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

// GUItool: begin automatically generated code
AudioSynthWaveform       lfo;      //xy=811.9335327148438,1025.9333591461182
AudioSynthWaveformDc     dc_osc_sub_freq_offset;            //xy=840.9333648681641,599.6000385284424
AudioSynthWaveformDc     dc_osc_freq;            //xy=1028.933578491211,348.5999641418457
AudioEffectEnvelope      envelope_lfo_delay;      //xy=1055.9335021972656,1025.9333543777466
AudioMixer4              mixer_osc_sub_freq;         //xy=1176.9333152770996,618.6001586914062
AudioSynthWaveformDc     dc_detune;            //xy=1296.2004089355469,494.0002074241638
AudioAmplifier           amp_lfo_osc_depth;           //xy=1298.9335174560547,927.9334092140198
AudioSynthWaveformDc     dc_filter_envelope_depth;            //xy=1492.3337631225586,1382.667025566101
AudioMixer4              mixer_osc_B_freq;         //xy=1520.9333190917969,504.59998321533203
AudioAmplifier           amp_filter_lfo_depth;           //xy=1699.9334716796875,1267.9333686828613
AudioEffectEnvelope      envelope_filter;      //xy=1702.6003112792969,1382.6003742218018
AudioSynthWaveformDc     dc_osc_B_pulse_width;            //xy=1766.9334602355957,546.933349609375
AudioSynthWaveformDc     dc_osc_A_pulse_width;            //xy=1793.9334602355957,405.2667155265808
AudioMixer4              mixer_filter_mod;         //xy=1983.93359375,1387.9333763122559
AudioSynthWaveformModulated osc_A;   //xy=2019.33349609375,375.33330726623535
AudioSynthWaveformModulated osc_sub;   //xy=2018.9335594177246,636.1334228515625
AudioSynthWaveformModulated osc_B;   //xy=2019.6671142578125,526.666748046875
AudioSynthNoisePink      pink_noise;          //xy=2019.9334754943848,745.9333267211914
AudioMixer4              mixer;         //xy=2319.000259399414,580.3332901000977
AudioFilterStateVariable filter;        //xy=2503.9999084472656,945.3333015441895
AudioEffectEnvelope      envelope_amp;      //xy=2694.99991607666,943.3332710266113
AudioAmplifier           amp_output;           //xy=2874.9331398010254,942.9333372116089
AudioOutputI2S           i2s1;           //xy=3034.00004196167,942.333270072937
AudioConnection          patchCord1(lfo, envelope_lfo_delay);
AudioConnection          patchCord2(dc_osc_sub_freq_offset, 0, mixer_osc_sub_freq, 1);
AudioConnection          patchCord3(dc_osc_freq, 0, osc_A, 0);
AudioConnection          patchCord4(dc_osc_freq, 0, mixer_osc_B_freq, 0);
AudioConnection          patchCord5(dc_osc_freq, 0, mixer_osc_sub_freq, 0);
AudioConnection          patchCord6(envelope_lfo_delay, amp_filter_lfo_depth);
AudioConnection          patchCord7(envelope_lfo_delay, amp_lfo_osc_depth);
AudioConnection          patchCord8(mixer_osc_sub_freq, 0, osc_sub, 0);
AudioConnection          patchCord9(dc_detune, 0, mixer_osc_B_freq, 1);
AudioConnection          patchCord10(dc_filter_envelope_depth, envelope_filter);
AudioConnection          patchCord11(mixer_osc_B_freq, 0, osc_B, 0);
AudioConnection          patchCord12(amp_filter_lfo_depth, 0, mixer_filter_mod, 0);
AudioConnection          patchCord13(envelope_filter, 0, mixer_filter_mod, 1);
AudioConnection          patchCord14(dc_osc_B_pulse_width, 0, osc_B, 1);
AudioConnection          patchCord15(dc_osc_A_pulse_width, 0, osc_A, 1);
AudioConnection          patchCord16(mixer_filter_mod, 0, filter, 1);
AudioConnection          patchCord17(osc_A, 0, mixer, 0);
AudioConnection          patchCord18(osc_sub, 0, mixer, 2);
AudioConnection          patchCord19(osc_B, 0, mixer, 1);
AudioConnection          patchCord20(pink_noise, 0, mixer, 3);
AudioConnection          patchCord21(mixer, 0, filter, 0);
AudioConnection          patchCord22(filter, 0, envelope_amp, 0);
AudioConnection          patchCord23(envelope_amp, amp_output);
AudioConnection          patchCord24(amp_output, 0, i2s1, 0);
AudioConnection          patchCord25(amp_output, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=2774.9998664855957,1006.3332748413086
// GUItool: end automatically generated code

















// CONSTANTS
const uint8_t HELD_NOTES_COUNT = 8;
const float MAX_OSC_LEVEL = 0.2;
const float PROGMEM CONSTANT_POWER[128] = {0.00000, 0.08874, 0.12549, 0.15369, 0.17747, 0.19842, 0.21736, 0.23477, 0.25098, 0.26621, 0.28061, 0.29430, 0.30739, 0.31994, 0.33202, 0.34367, 0.35494, 0.36587, 0.37647, 0.38679, 0.39684, 0.40664, 0.41621, 0.42556, 0.43471, 0.44368, 0.45246, 0.46108, 0.46954, 0.47786, 0.48603, 0.49406, 0.50196, 0.50975, 0.51741, 0.52497, 0.53241, 0.53976, 0.54700, 0.55415, 0.56121, 0.56819, 0.57507, 0.58188, 0.58861, 0.59526, 0.60183, 0.60834, 0.61478, 0.62115, 0.62746, 0.63370, 0.63988, 0.64601, 0.65207, 0.65808, 0.66404, 0.66994, 0.67579, 0.68159, 0.68734, 0.69305, 0.69871, 0.70432, 0.70989, 0.71541, 0.72089, 0.72633, 0.73173, 0.73709, 0.74242, 0.74770, 0.75295, 0.75816, 0.76333, 0.76847, 0.77358, 0.77865, 0.78369, 0.78870, 0.79368, 0.79862, 0.80354, 0.80842, 0.81328, 0.81810, 0.82290, 0.82767, 0.83241, 0.83713, 0.84182, 0.84648, 0.85112, 0.85574, 0.86032, 0.86489, 0.86943, 0.87394, 0.87844, 0.88291, 0.88736, 0.89178, 0.89619, 0.90057, 0.90493, 0.90927, 0.91359, 0.91789, 0.92217, 0.92643, 0.93067, 0.93489, 0.93909, 0.94327, 0.94744, 0.95158, 0.95571, 0.95982, 0.96392, 0.96799, 0.97205, 0.97609, 0.98012, 0.98413, 0.98812, 0.99209, 0.99606, 1.00000};
const uint16_t PROGMEM ENV_TIMES_MS[128] = {1, 2, 4, 6, 9, 14, 20, 26, 33, 41, 49, 58, 67, 78, 89, 99, 111, 124, 136, 150, 164, 178, 192, 209, 224, 241, 258, 276, 295, 314, 333, 353, 374, 395, 418, 440, 464, 489, 513, 539, 565, 592, 621, 650, 680, 710, 742, 774, 808, 843, 878, 915, 952, 991, 1031, 1073, 1114, 1158, 1202, 1250, 1297, 1346, 1396, 1448, 1502, 1558, 1614, 1676, 1735, 1794, 1864, 1923, 1994, 2065, 2136, 2207, 2289, 2360, 2443, 2525, 2620, 2702, 2797, 2891, 2985, 3092, 3186, 3292, 3410, 3516, 3634, 3752, 3882, 4012, 4142, 4272, 4413, 4567, 4708, 4862, 5027, 5180, 5357, 5522, 5699, 5888, 6077, 6278, 6478, 6691, 6903, 7127, 7351, 7587, 7835, 8083, 8343, 8614, 8885, 9169, 9464, 9770, 10077, 10408, 10738, 11080, 11434, 11700};
const uint16_t PROGMEM FILTER_CUTOFF_FREQS_HZ[256] = {20, 21, 22, 23, 24, 26, 27, 28, 29, 31, 32, 33, 34, 35, 36, 38, 39, 40, 41, 43, 44, 46, 47, 49, 50, 52, 53, 55, 57, 59, 61, 63, 65, 68, 70, 73, 76, 78, 81, 84, 87, 91, 94, 98, 102, 106, 110, 114, 119, 123, 128, 133, 138, 144, 149, 155, 161, 167, 174, 181, 187, 195, 202, 210, 218, 226, 234, 243, 252, 261, 271, 281, 291, 301, 312, 323, 334, 346, 358, 370, 383, 395, 409, 422, 436, 451, 465, 480, 496, 512, 528, 544, 561, 578, 596, 614, 633, 652, 671, 691, 711, 732, 753, 774, 796, 818, 841, 865, 888, 913, 937, 962, 988, 1014, 1041, 1068, 1096, 1124, 1152, 1182, 1211, 1242, 1272, 1304, 1335, 1368, 1401, 1434, 1468, 1503, 1538, 1574, 1610, 1647, 1684, 1722, 1761, 1800, 1840, 1881, 1922, 1964, 2006, 2049, 2093, 2137, 2182, 2227, 2274, 2320, 2368, 2416, 2465, 2515, 2565, 2616, 2668, 2720, 2773, 2827, 2881, 2936, 2992, 3049, 3106, 3164, 3223, 3283, 3343, 3404, 3466, 3529, 3592, 3656, 3721, 3787, 3853, 3921, 3989, 4058, 4127, 4198, 4269, 4341, 4414, 4488, 4563, 4638, 4715, 4792, 4870, 4949, 5029, 5109, 5191, 5273, 5357, 5441, 5526, 5612, 5699, 5787, 5876, 5965, 6056, 6147, 6240, 6333, 6427, 6523, 6619, 6716, 6814, 6913, 7013, 7114, 7216, 7319, 7424, 7529, 7635, 7742, 7850, 7959, 8069, 8180, 8292, 8405, 8519, 8634, 8751, 8868, 8986, 9106, 9226, 9348, 9471, 9594, 9719, 9845, 9972, 10100, 10230, 10360, 10491, 10624, 10758, 10893, 11029, 11166, 11304, 11443, 11584, 11726, 11869, 12000};
const float PROGMEM LFO_FREQS_HZ[128] = {0.10000, 0.10140, 0.10561, 0.11263, 0.12245, 0.13508, 0.15051, 0.16875, 0.18980, 0.21365, 0.24031, 0.26977, 0.30204, 0.33712, 0.37500, 0.41569, 0.45918, 0.50548, 0.55459, 0.60651, 0.66122, 0.71875, 0.77908, 0.84222, 0.90816, 0.97691, 1.04847, 1.12283, 1.20000, 1.27997, 1.36276, 1.44834, 1.53673, 1.62793, 1.72194, 1.81875, 1.91837, 2.02079, 2.12602, 2.23406, 2.34490, 2.45855, 2.57500, 2.69426, 2.81633, 2.94120, 3.06888, 3.19936, 3.33265, 3.46875, 3.60765, 3.74936, 3.89388, 4.04120, 4.19133, 4.34426, 4.50000, 4.65855, 4.81990, 4.98406, 5.15102, 5.32079, 5.49337, 5.66875, 5.84694, 6.02793, 6.21173, 6.39834, 6.58776, 6.77997, 6.97500, 7.17283, 7.37347, 7.57691, 7.78316, 7.99222, 8.20408, 8.41875, 8.63622, 8.85651, 9.07959, 9.30548, 9.53418, 9.76569, 10.00000, 10.53542, 12.14170, 14.81882, 18.56679, 23.38561, 29.27528, 36.23580, 44.26717, 53.36939, 63.54246, 74.78637, 87.10114, 100.48675, 114.94321, 130.47052, 147.06869, 164.73770, 183.47756, 203.28826, 224.16982, 246.12223, 269.14548, 293.23959, 318.40454, 344.64035, 371.94700, 400.32450, 429.77285, 460.29205, 491.88210, 524.54300, 558.27474, 593.07734, 628.95078, 665.89508, 703.91022, 742.99621, 783.15306, 824.38075, 866.67929, 910.04867, 954.48891, 1000.00000};
const float PROGMEM NOTE_FREQ_DC[128] = {-0.57500, -0.56667, -0.55833, -0.55000, -0.54167, -0.53333, -0.52500, -0.51667, -0.50833, -0.50000, -0.49167, -0.48333, -0.47500, -0.46667, -0.45833, -0.45000, -0.44167, -0.43333, -0.42500, -0.41667, -0.40833, -0.40000, -0.39167, -0.38333, -0.37500, -0.36667, -0.35833, -0.35000, -0.34167, -0.33333, -0.32500, -0.31667, -0.30833, -0.30000, -0.29167, -0.28333, -0.27500, -0.26667, -0.25833, -0.25000, -0.24167, -0.23333, -0.22500, -0.21667, -0.20833, -0.20000, -0.19167, -0.18333, -0.17500, -0.16667, -0.15833, -0.15000, -0.14167, -0.13333, -0.12500, -0.11667, -0.10833, -0.10000, -0.09167, -0.08333, -0.07500, -0.06667, -0.05833, -0.05000, -0.04167, -0.03333, -0.02500, -0.01667, -0.00833, 0.00000, 0.00833, 0.01667, 0.02500, 0.03333, 0.04167, 0.05000, 0.05833, 0.06667, 0.07500, 0.08333, 0.09167, 0.10000, 0.10833, 0.11667, 0.12500, 0.13333, 0.14167, 0.15000, 0.15833, 0.16667, 0.17500, 0.18333, 0.19167, 0.20000, 0.20833, 0.21667, 0.22500, 0.23333, 0.24167, 0.25000, 0.25833, 0.26667, 0.27500, 0.28333, 0.29167, 0.30000, 0.30833, 0.31667, 0.32500, 0.33333, 0.34167, 0.35000, 0.35833, 0.36667, 0.37500, 0.38333, 0.39167, 0.40000, 0.40833, 0.41667, 0.42500, 0.43333, 0.44167, 0.45000, 0.45833, 0.46667, 0.47500, 0.48333};

// GLOBALS
uint8_t filter_envelope_depth_cc_value = 0;
uint8_t filter_lfo_depth_cc_value = 0;
float glide_time_ms = 0;
uint8_t held_notes[HELD_NOTES_COUNT];
bool is_legato_enabled = true;

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
  osc_A.frequency(440.0);
  osc_A.frequencyModulation(10.0);

  dc_osc_A_pulse_width.amplitude(0.5);

  dc_osc_freq.amplitude(0.0);

  // OSCILLATOR B
  osc_B.begin(WAVEFORM_BANDLIMIT_SAWTOOTH);
  osc_B.amplitude(0.1);
  osc_B.frequency(440.0);
  osc_B.frequencyModulation(10.0);

  dc_osc_B_pulse_width.amplitude(0.75);

  dc_detune.amplitude(0.001);

  mixer_osc_B_freq.gain(0, 1.0);  // Note frequency
  mixer_osc_B_freq.gain(1, 1.0);  // Detune
  mixer_osc_B_freq.gain(2, 0.0);  // Not used
  mixer_osc_B_freq.gain(3, 0.0);  // Not used

  // OSCILLATOR SUB
  osc_sub.begin(WAVEFORM_SINE);
  osc_sub.amplitude(0.2);
  osc_sub.frequency(440.0);
  osc_sub.frequencyModulation(10.0);

  dc_osc_sub_freq_offset.amplitude(-0.1);

  mixer_osc_sub_freq.gain(0, 1.0);  // Note frequency
  mixer_osc_sub_freq.gain(1, 1.0);  // Offset (i.e. one octave down)
  mixer_osc_sub_freq.gain(2, 0.0);  // Not used
  mixer_osc_sub_freq.gain(3, 0.0);  // Not used

  // NOISE GENERATOR
  pink_noise.amplitude(0.1);

  //MIXER
  mixer.gain(0, 0.707 * MAX_OSC_LEVEL); // Osc A
  mixer.gain(1, 0.707 * MAX_OSC_LEVEL); // Osc B
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

  // Find the first unused slot in the note buffer
  int8_t new_note_index = -1;
  for (int8_t i = 0; i < HELD_NOTES_COUNT; i++) {
    // If new note is already being held - Ignore new note. Do not do anything. Return.
    if (held_notes[i] == note) {
      return;
    }

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
        is_legato_enabled = value == < 64;
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

