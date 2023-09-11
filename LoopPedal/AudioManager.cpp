#include "AudioManager.h"
AudioManager* AudioManager::instance = nullptr;

AudioManager::AudioManager() 
{
    patchCordKST = std::make_unique<AudioConnection>(mixerKST, 0, mixerOut, 0);
    patchCordHCC = std::make_unique<AudioConnection>(mixerHCC, 0, mixerOut, 1);
    patchCordReverb = std::make_unique<AudioConnection>(mixerOut, 0, reverb, 0); // Needs mixing with clean signal
    patchCordOutR = std::make_unique<AudioConnection>(mixerOut, 0, audioOutput, 0);
    patchCordOutL = std::make_unique<AudioConnection>(mixerOut, 0, audioOutput, 1);

    instance = this;
    sequencer = std::make_unique<Sequencer>(mixerKST, mixerHCC);
}

void AudioManager::setup()
{
    AudioMemory(12);
    sgtl5000.enable();
    sgtl5000.volume(0.2);

    mixerKST.gain(0, 1.0);
    mixerKST.gain(1, 1.0);
    mixerKST.gain(2, 1.0);
    mixerKST.gain(3, 1.0);
    mixerHCC.gain(0, 1.0);
    mixerHCC.gain(1, 1.0);
    mixerHCC.gain(2, 1.0);
    mixerHCC.gain(3, 1.0);
    mixerOut.gain(0, 1.0);
    mixerOut.gain(1, 1.0);
    mixerOut.gain(2, 1.0);
    mixerOut.gain(3, 1.0);

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