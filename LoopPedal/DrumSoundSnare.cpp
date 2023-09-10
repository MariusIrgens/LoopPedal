#include "DrumSoundSnare.h"

DrumSoundSnare::DrumSoundSnare(int mixerChannel, AudioMixer4& mixer)
    : DrumSound(mixerChannel, mixer), patchCord(drumSynth, 0, mixer, mixerChannel)
{
    // Initialize the noise or other modules as necessary
}

void DrumSoundSnare::trigger(int velocity) {

    drumSynth.frequency(440.0);
    drumSynth.length(50);
    drumSynth.noteOn();

    if (debugMode) {
        //Serial.print("Snare sound");
    }
}