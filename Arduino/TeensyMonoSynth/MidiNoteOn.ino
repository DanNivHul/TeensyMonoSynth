void myNoteOn(byte channel, byte note, byte velocity) {
  Serial.println("Note on");

  int8_t new_note_index = -1;
  for (int8_t i = 0; i < HELD_NOTES_COUNT; i++) {
    // If new note is already being held - Ignore new note. Do not do anything. Return.
    if (held_notes[i] == note) {
      return;
    }

    // Find the first unused slot in the note buffer
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

  dc_note_velocity.amplitude(velocity / 127.0, 1);

  if (new_note_index == 0) {
    // If no other note is being held - Play new note immediately. Update volume with respect to velocity. Do trigger envelopes.
    dc_osc_freq.amplitude(NOTE_FREQ_DC[note], 0.0);
    
    triggerEnvelopes();
  } else {  
    // If a note is being held 

    // If glide is enabled, glide to new note. 
    // If glide not enabled, immediately change to new note.
    float actual_glide_time_ms = is_glide_enabled ? GLIDE_TIME_MS : 0.0;
    dc_osc_freq.amplitude(NOTE_FREQ_DC[note], actual_glide_time_ms);
    
    // If legato mode is enabled - do not trigger envelopes.
    // If legato mode is not enabled - do trigger envelopes.
    if (!is_legato_enabled) {
      triggerEnvelopes();
    }
  }
  
  // AudioInterrupts();  // Enable the audio library update interrupt. Any settings changed will all take effect at the same time.
}

void triggerEnvelopes() {
  envelope_amp.noteOn();
  envelope_filter.noteOn();
  envelope_lfo_delay.noteOn();
  dc_pitch_env.amplitude(pitch_envelope_depth);
  dc_pitch_env.amplitude(0.0, pitch_envelope_decay_time_ms);
}