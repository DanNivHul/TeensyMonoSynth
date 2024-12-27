# HIGH PRIORITY

// todo - change square to pulse for Osc A and Osc B and add pulse width ccs for both (on second thought, if you have lfo and envelope to pulse width, do you need manual set of pulse width? I guess helpful for testing?)
// todo - lfo to pulse width. cc for depth
// todo - envelope to pulse width. cc for depth
// todo - expose full adsr parameters to cc. filter and amp share same settings
// todo - envelope to osc pitch
// todo - set volume to 1
// todo - sub waveform select (square or 25% pulse?)
// done - add bandpass option for filter
// done - lfo to osc pitches
// done - option for legato mode (retrigger envelopes vs don't)
// done - better note on / off. at the moment. store previous notes in buffer and return to them if note off not received
// done - glide


// ====================================================================================================
// TODO - MID PRIORITY
// ====================================================================================================
// todo - finalise glide times. or alternatively have a constant glide time and either turn it on or off
// todo - should lfo to osc be bipolar? currently it is unipolar?
// todo - fine tune range for lfo to osc. currently goes up to 1 octave, but not sure how useful that is
// todo - add detune to 3rd, 5th, etc?
// todo - detune unipolar
// todo - pitch bend
// todo - mod wheel to either filter cutoff or lfo depth?
// todo - note velocity to volume. cc for depth
// todo - note velocity to filter cutoff. cc for depth
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