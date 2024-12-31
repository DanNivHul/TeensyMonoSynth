void myPitchBend(byte channel, int bend) {
  dc_pitch_bend.amplitude(bend / 8192.0 * MAX_PITCH_BEND);
}