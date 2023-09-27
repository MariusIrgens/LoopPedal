#include "AudioManager.h"
#include "SystemController.h"

AudioManager* AudioManager::instance = nullptr;

AudioManager::AudioManager(SystemController* sysController) : systemController(sysController)
{
    // AUDIO
    
    // FROM audio TO audio-mixer
    patchCordIn1_AudMix = std::make_unique<AudioConnection>(audioInput, 0, mixerAudio, 0);
    patchCordIn2_AudMix = std::make_unique<AudioConnection>(audioInput, 1, mixerAudio, 1);

    // FROM audio-mixer TO loop-mixer (dry)
    patchCordAudMix_LoopMix = std::make_unique<AudioConnection>(mixerAudio, 0, mixerLooper, 0);

    // FROM loop-mixer TO end-mixer
    patchCordLoopMix_EndMix = std::make_unique<AudioConnection>(mixerLooper, 0, mixerEnd, 2);

    // DRUMS
    
    // FROM drums TO drum-FX-mixer
    patchCordKST_DrumMix = std::make_unique<AudioConnection>(mixerKST, 0, mixerDrums, 0);
    patchCordHCC_DrumMix = std::make_unique<AudioConnection>(mixerHCC, 0, mixerDrums, 1);

    // FROM drum-FX-mixer TO end-mixer (dry)
    patchCordDrumMix_EndMix = std::make_unique<AudioConnection>(mixerDrums, 0, mixerEnd, 0);

    // FROM drum-FX-mixer TO reverb TO end-mixer (wet)
    patchCordDrumMix_Reverb = std::make_unique<AudioConnection>(mixerDrums, 0, reverb, 0);
    patchCordReverb_EndMix = std::make_unique<AudioConnection>(reverb, 0, mixerEnd, 1);

    // FROM end-mixer TO output
    patchCordEndMix_AudioOutR = std::make_unique<AudioConnection>(mixerEnd, 0, audioOutput, 0);
    patchCordEndMix_AudioOutL = std::make_unique<AudioConnection>(mixerEnd, 0, audioOutput, 1);

    instance = this;
    looper = std::make_unique<Looper>(this, mixerAudio, mixerLooper);
    sequencer = std::make_unique<Sequencer>(this, mixerKST, mixerHCC);
}

void AudioManager::setup()
{
    // Codec
    AudioMemory(1500);
    sgtl5000.enable();
    sgtl5000.volume(1.0);

    // Audio
    mixerAudio.gain(0, 0.0);// Audio 1
    mixerAudio.gain(0, 0.0);// Audio 2
    //amplifier.gain(0.5);    // Audio amp

    // Drums
    mixerKST.gain(0, 1.0); // Kick
    mixerKST.gain(1, 1.0); // Snare
    mixerKST.gain(2, 1.0); // TomHigh
    mixerKST.gain(3, 1.0); // TomLow
    mixerHCC.gain(0, 1.0); // Hihat Closed
    mixerHCC.gain(1, 1.0); // Hihat Open
    mixerHCC.gain(2, 1.0); // Cymbal
    mixerHCC.gain(3, 0.0); // -
    mixerDrums.gain(0, 0.0);  // KST 
    mixerDrums.gain(1, 0.0);  // HCC
    mixerDrums.gain(2, 0.0);  // -
    mixerDrums.gain(3, 0.0);  // -

    // End-mixer
    mixerEnd.gain(0, 0.2); // Drums (dry)
    mixerEnd.gain(1, 0.0); // Drums reverb (wet)
    mixerEnd.gain(2, 1.0); // Audio thru
    mixerEnd.gain(3, 1.0); // Audio Loop

    // Effects
    reverb.damping(0.0);
    reverb.roomsize(0.01);

    // Timers
    drumTimer.begin(stepUpdate, sixteenthNote);
    updateTimer.begin(synthUpdate, UPDATE_DELTATIME);
    looperTimer.begin(looperUpdate, LOOPER_DELTATIME);
}

void AudioManager::stepUpdate() {

    // Advance sequencer with a 16th step
    instance->sequencer->nextStep();

    // Metronome
    if (instance->sequencer->readCurrentStep() == 0) // Sequence start
    {
        instance->systemController->blinkLED(1);
    }
    else if (instance->sequencer->readCurrentStep() % instance->sequencer->getPatternLength() == 0) // Major beats
    {
        instance->systemController->blinkLED(2);
    }
    else if (instance->sequencer->readCurrentStep() % 4 == 0) // Others
    {
        instance->systemController->blinkLED(3);
    }
    else
    {
        instance->systemController->blinkLED(0); // Turn off
    }
}

void AudioManager::synthUpdate()
{
    instance->sequencer->update(UPDATE_DELTATIME);
}

void AudioManager::looperUpdate() 
{
    instance->looper->update();
}

void AudioManager::setDrumTimerInterval(int newSixteenthNote) {
    sixteenthNote = newSixteenthNote;
    drumTimer.end();
    drumTimer.begin(stepUpdate, sixteenthNote);
}

void AudioManager::setAudioVolume(float volume)
{
    float regulatedAudioVolume = volume;
    if (regulatedAudioVolume < audioVolume - 0.01 || regulatedAudioVolume > audioVolume + 0.01)
    {
        audioVolume = regulatedAudioVolume;
        std::string message = "Audio volume: " + std::to_string(audioVolume);
        Serial.println(message.c_str());
        mixerAudio.gain(0, audioVolume);
        mixerAudio.gain(1, audioVolume);
    }
}

void AudioManager::setDrumVolume(float volume)
{
    float regulatedDrumVolume = volume / 10.0f;
    if (regulatedDrumVolume < drumVolume - 0.01 || regulatedDrumVolume > drumVolume + 0.01)
    {
        drumVolume = regulatedDrumVolume;
        std::string message = "Drum volume: " + std::to_string(drumVolume);
        Serial.println(message.c_str());
        mixerDrums.gain(0, drumVolume);
        mixerDrums.gain(1, drumVolume);
    }
}

Looper* AudioManager::getLooper()
{
    return looper.get();
}