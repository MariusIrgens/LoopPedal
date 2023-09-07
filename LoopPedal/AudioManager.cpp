#include "AudioManager.h"

AudioManager::AudioManager() : 
    patchCord1(audioInput, 1, amplifier, 0),  // right channel
    patchCord3(amplifier, 0, audioOutput, 0) // left channel
{

}

void AudioManager::setup()
{
    AudioMemory(12);
    sgtl5000.enable();
    sgtl5000.volume(0.5);
    amplifier.gain(8.0);
}

void AudioManager::loop()
{

}