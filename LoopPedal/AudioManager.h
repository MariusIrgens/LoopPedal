#ifndef _AUDIOMANAGER_h
#define _AUDIOMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <Audio.h>
#include <memory>
#include "Sequencer.h"
#include "Looper.h"

#define UPDATE_DELTATIME 25000 // How often update is run, resulting in its resolution (used for envelopes)
#define LOOPER_DELTATIME 20000

class SystemController;

class AudioManager {
public:
    AudioManager(SystemController* sysController);
    void setup();
    static void stepUpdate();
    static void synthUpdate();
    static void looperUpdate();
    void setDrumTimerInterval(int newSixteenthNote);
    void setAudioVolume(float volume);
    void setDrumVolume(float volume);
    Looper* getLooper();

private:
    SystemController* systemController;
    static AudioManager* instance;
    std::unique_ptr<Looper> looper;
    std::unique_ptr<Sequencer> sequencer;
    IntervalTimer drumTimer;
    IntervalTimer updateTimer;
    IntervalTimer looperTimer;

    AudioControlSGTL5000 sgtl5000; // SGTL5000 audio codec control object
    AudioInputI2S audioInput; // audio input
    //AudioAmplifier amplifier; // Amplifier for audio
    AudioOutputI2S audioOutput; // Stereo audio output
    AudioEffectFreeverb reverb; // Effect

    AudioMixer4 mixerAudio; // Mixer for both audio inputs
    AudioMixer4 mixerLooper; // Mixer for dry audio and loop(s?)

    AudioMixer4 mixerKST; // Mixer for drums 1
    AudioMixer4 mixerHCC; // Mixer for drums 2
    AudioMixer4 mixerDrums; // Mixer for all drums
    AudioMixer4 mixerEnd; // End Mixer

    std::unique_ptr<AudioConnection> patchCordIn1_AudMix;
    std::unique_ptr<AudioConnection> patchCordIn2_AudMix;
    std::unique_ptr<AudioConnection> patchCordAudMix_LoopMix;
    std::unique_ptr<AudioConnection> patchCordLoopMix_EndMix;

    std::unique_ptr<AudioConnection> patchCordKST_DrumMix;
    std::unique_ptr<AudioConnection> patchCordHCC_DrumMix;
    std::unique_ptr<AudioConnection> patchCordDrumMix_EndMix;
    std::unique_ptr<AudioConnection> patchCordDrumMix_Reverb;
    std::unique_ptr<AudioConnection> patchCordReverb_EndMix;
    std::unique_ptr<AudioConnection> patchCordEndMix_AudioOutR;
    std::unique_ptr<AudioConnection> patchCordEndMix_AudioOutL;

    uint32_t lastTriggerTime = 0; // Used to trigger drum sound periodically

    int sixteenthNote = 125000;

    float drumVolume = 0.0f;
    float audioVolume = 0.0f;

};

#endif
