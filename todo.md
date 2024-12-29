# Teensy Monosynth To-Do List

## High Priority
- [ ] set volume to 1
- [x] envelope to osc pitch. have it's own rate and depth
- [x] remove pulse width cc stuff on arduino code and web programmer
- [x] change pulse to square for Osc A and Osc B
- [x] change web programmer to not need spanid in data provided
- [x] add bandpass option for filter
- [x] lfo to osc pitches
- [x] option for legato mode (retrigger envelopes vs don't)
- [x] better note on / off. at the moment. store previous notes in buffer and return to them if note off not received
- [x] glide


## Medium Priority
- [ ] finalise glide times. or alternatively have a constant glide time and either turn it on or off
- [ ] fine tune envelope times
- [ ] should lfo to osc be bipolar? currently it is unipolar?
- [ ] fine tune range for lfo to osc. currently goes up to 1 octave, but not sure how useful that is
- [ ] pitch bend
- [ ] try supersaw as an oscillator option
- [ ] mod wheel to either filter cutoff or lfo depth?
- [ ] note velocity to volume. cc for depth
- [ ] note velocity to filter cutoff. cc for depth
- [ ] filter cutoff envelope bipolar. 
- [ ] filter cutoff lfo bipolar
- [ ] white noise as lfo source
- [ ] lfo option where each note on triggers a new random value and sustains it until the next note on 
- [ ] send midi over usb to update web programmer
- [ ] logical operator distortion - type and crossfade distortion amount
- [ ] x-mod of oscillators
- [x] fine tune pitch env decay times
- [x] add detune to 3rd, 5th, etc?
- [x] crossfade between osc A and osc B using constant power instead of linear crossfade


## Low Priority
- [ ] sub waveform select (square... maybe triangle too?). Possibly -1 and -2 octave down option?
- [ ] option for auto-glide (always glide vs only glide when notes overlap)
- [ ] finetune lfo rate range. 
- [ ] option to reset phase of osc when note on event is triggered. cc for that
- [ ] option to reset lfo phase when note on event is triggered. cc for that
- [ ] sync lfo to midi clock. rate becomes clock divider
- [ ] someway of storing presets? online editor
- [ ] led for midi rx
- [ ] led for lfo rate
- [ ] midi channel rx. set by web programmer. store and load in eeprom.
- [ ] poly aftertouch? a
- [ ] unison option?

## Notes
- Pulse waveform implementation sucks on Teensy, so stick with square wave