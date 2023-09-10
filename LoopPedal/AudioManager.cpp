#include "AudioManager.h"
AudioManager* AudioManager::instance = nullptr;

AudioManager::AudioManager() :
    //sequencer(mixer1, mixer2),
    kick(0, mixer1),
    patchCord1(drum, 0, mixer3, 3),
    patchCord2(mixer1, 0, mixer3, 0),
    patchCord3(mixer2, 0, mixer3, 1),
    patchCord4(mixer3, 0, amplifier, 0),
    patchCord5(amplifier, 0, audioOutput, 0), 
    patchCord6(amplifier, 0, audioOutput, 1)
{
    instance = this;
}

void AudioManager::setup()
{
    AudioMemory(12);
    sgtl5000.enable();
    sgtl5000.volume(0.5);

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

    drumTimer.begin(drumPatternISR, 125000);  // 125000 microseconds = 125ms
}

void AudioManager::loop()
{
    if (millis() - lastTriggerTime > 1000) { // Check if 1 second has passed
        //drum.frequency(800.0);
        //drum.length(500);
        //drum.noteOn();
        //kick.trigger();
        lastTriggerTime = millis(); // Update the last trigger time
    }
}

void AudioManager::drumPatternISR() {
    //instance->sequencer.nextStep();
    instance->kick.trigger();
}