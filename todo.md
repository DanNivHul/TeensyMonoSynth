# Teensy Monosynth To-Do List

## High Priority
- [ ] change square to pulse for Osc A and Osc B and add pulse width ccs for both (on second thought, if you have lfo and envelope to pulse width, do you need manual set of pulse width? I guess helpful for testing?)
- [ ] lfo to pulse width. cc for depth
- [ ] envelope to pulse width. cc for depth
- [ ] expose full adsr parameters to cc. filter and amp share same settings
- [ ] envelope to osc pitch
- [ ] set volume to 1
- [ ] sub waveform select (square or 25% pulse?)
- [x] add bandpass option for filter
- [x] lfo to osc pitches
- [x] option for legato mode (retrigger envelopes vs don't)
- [x] better note on / off. at the moment. store previous notes in buffer and return to them if note off not received
- [x] glide


## Medium Priority
- [ ] finalise glide times. or alternatively have a constant glide time and either turn it on or off
- [ ] should lfo to osc be bipolar? currently it is unipolar?
- [ ] fine tune range for lfo to osc. currently goes up to 1 octave, but not sure how useful that is
- [ ] add detune to 3rd, 5th, etc?
- [ ] detune unipolar
- [ ] pitch bend
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
- [x] crossfade between osc A and osc B using constant power instead of linear crossfade


## Low Priority
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