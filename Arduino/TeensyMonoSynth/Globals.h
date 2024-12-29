// GLOBALS
uint8_t filter_envelope_depth_cc_value = 0;
uint8_t filter_lfo_depth_cc_value = 0;
float glide_time_ms = 0;
uint8_t held_notes[HELD_NOTES_COUNT];
bool is_legato_enabled = true;
float detune_amount = 0.001;
float semitone_offset = 0.0;
float pitch_envelope_depth = 0.0;
float pitch_envelope_decay_time_ms = 1.0;