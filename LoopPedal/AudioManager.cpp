#include "AudioManager.h"
AudioManager* AudioManager::instance = nullptr;

AudioManager::AudioManager() 
{
    // To FX mixer
    patchCordKST_FX = std::make_unique<AudioConnection>(mixerKST, 0, mixerFX, 0);
    patchCordHCC_FX = std::make_unique<AudioConnection>(mixerHCC, 0, mixerFX, 1);

    // To effects
    patchCordFX_Out = std::make_unique<AudioConnection>(mixerFX, 0, mixerOut, 0);
    patchCordFX_Reverb = std::make_unique<AudioConnection>(mixerFX, 0, reverb, 0);
    patchCordReverb_Out = std::make_unique<AudioConnection>(reverb, 0, mixerOut, 1);

    // To output
    patchCordOut_AudioOutR = std::make_unique<AudioConnection>(mixerOut, 0, audioOutput, 0);
    patchCordOut_AudioOutL = std::make_unique<AudioConnection>(mixerOut, 0, audioOutput, 1);

    instance = this;
    sequencer = std::make_unique<Sequencer>(this, mixerKST, mixerHCC);
}

void AudioManager::setup()
{
    AudioMemory(12);
    sgtl5000.enable();
    sgtl5000.volume(0.2);

    mixerKST.gain(0, 1.0); // Kick
    mixerKST.gain(1, 1.0); // Snare
    mixerKST.gain(2, 1.0); // TomHigh
    mixerKST.gain(3, 1.0); // TomLow
    mixerHCC.gain(0, 1.0); // Hihat Closed
    mixerHCC.gain(1, 1.0); // Hihat Open
    mixerHCC.gain(2, 1.0); // Clap
    mixerHCC.gain(3, 1.0); // Cymbal
    mixerFX.gain(0, 1.0);
    mixerFX.gain(1, 1.0);
    //mixerFX.gain(2, 1.0);
    //mixerFX.gain(3, 1.0);
    mixerOut.gain(0, 1.0); // Direct
    mixerOut.gain(1, 0.2); // Reverb
    //mixerOut.gain(2, 1.0);
    //mixerOut.gain(3, 1.0);

    reverb.damping(0.0);
    reverb.roomsize(0.01);

    drumTimer.begin(stepSequence, sixteenthNote); 
    updateTimer.begin(update, UPDATE_DELTATIME);
}

void AudioManager::loop()
{

}

void AudioManager::stepSequence() {
    instance->sequencer->nextStep();
}

void AudioManager::update()
{
    instance->sequencer->update(UPDATE_DELTATIME);
}

void AudioManager::setDrumTimerInterval(int newSixteenthNote) {
    sixteenthNote = newSixteenthNote;
    drumTimer.end();
    drumTimer.begin(stepSequence, sixteenthNote);
}
