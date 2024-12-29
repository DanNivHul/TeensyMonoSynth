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

      // If glide is enabled, glide to new note. 
      // If glide not enabled, immediately change to new note.
      float actual_glide_time_ms = is_glide_enabled ? GLIDE_TIME_MS : 0.0;
      dc_osc_freq.amplitude(NOTE_FREQ_DC[next_most_recently_held_note], actual_glide_time_ms);
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