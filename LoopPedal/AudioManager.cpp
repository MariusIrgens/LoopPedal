#include "AudioManager.h"
AudioManager* AudioManager::instance = nullptr;

AudioManager::AudioManager() :
    patchCord1(drum, 0, mixer3, 3),
    patchCord2(mixer1, 0, mixer3, 0),
    patchCord3(mixer2, 0, mixer3, 1),
    patchCord4(mixer3, 0, amplifier, 0),
    patchCord5(amplifier, 0, audioOutput, 0), 
    patchCord6(amplifier, 0, audioOutput, 1)
{
    instance = this;
    sequencer = std::make_unique<Sequencer>(mixer1, mixer2);
}

void AudioManager::setup()
{
    AudioMemory(12);
    sgtl5000.enable();
    sgtl5000.volume(0.2);

    amplifier.gain(1.0);

    mixer1.gain(0, 1.0); 
    mixer1.gain(1, 1.0);
    mixer1.gain(2, 1.0);
    mixer1.gain(3, 1.0);
    mixer2.gain(0, 1.0);
    mixer2.gain(1, 1.0);
    mixer2.gain(2, 1.0);
    mixer2.gain(3, 1.0);
    mixer3.gain(0, 1.0);
    mixer3.gain(1, 1.0);
    mixer3.gain(2, 1.0);
    mixer3.gain(3, 1.0);

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