#include "DrumSoundKick.h"

DrumSoundKick::DrumSoundKick(int mixerChannel, AudioMixer4& mixer)
    : DrumSound(mixerChannel, mixer), patchCord(sineOsc, 0, mixer, mixerChannel), envelopeFreq(350.0f, 20.0f, 5, 250, 0.1f)
{
    // Initialize the oscillator or other modules as necessary
}

void DrumSoundKick::trigger(int velocity) {
    // trigger will reset to base frequency, and trigger envelope
    envelopeFreq.start();
    envelopeFreq.setDecayTime(100);

    if (debugMode) {
        //Serial.print("Kick sound");
    }
}

void DrumSoundKick::update(int deltaTime) {
    envelopeFreq.update(deltaTime);
    sineOsc.frequency(envelopeFreq.read());
}