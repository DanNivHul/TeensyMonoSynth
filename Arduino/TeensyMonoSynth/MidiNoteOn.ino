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

  if (new_note_index == 0) {
    // If no other note is being held - Play new note immediately. Do trigger envelope.
    dc_osc_freq.amplitude(NOTE_FREQ_DC[note], 0.0);
    envelope_amp.noteOn();
    envelope_filter.noteOn();
    envelope_lfo_delay.noteOn();
    envelope.noteOn();
  } else {
    // If a note is being held - Glide to new note. 
    dc_osc_freq.amplitude(NOTE_FREQ_DC[note], glide_time_ms);
    
    // If legato mode is enabled - do not trigger envelope.
    // If legato mode is not enabled - do trigger envelope.
    if (!is_legato_enabled) {
      envelope_amp.noteOn();
      envelope_filter.noteOn();
      envelope_lfo_delay.noteOn();
      envelope.noteOn();
    }
  }
  
  // AudioInterrupts();  // Enable the audio library update interrupt. Any settings changed will all take effect at the same time.
}