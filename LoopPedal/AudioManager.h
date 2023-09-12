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

#define UPDATE_DELTATIME 25000 // How often update is run, resulting in its resolution

class AudioManager {
public:
    AudioManager();
    void setup();
    void loop();
    static void stepSequence();
    static void update();

private:
    static AudioManager* instance;
    std::unique_ptr<Sequencer> sequencer;
    IntervalTimer drumTimer;
    IntervalTimer updateTimer;

    AudioControlSGTL5000 sgtl5000; // SGTL5000 audio codec control object
    AudioInputI2S audioInput; // Stereo audio input
    AudioAmplifier amplifier; // Amplifier for volume boost
    AudioOutputI2S audioOutput; // Stereo audio output
    AudioMixer4 mixerKST;
    AudioMixer4 mixerHCC;
    AudioMixer4 mixerFX;
    AudioMixer4 mixerOut;
    AudioEffectFreeverb reverb;

    std::unique_ptr<AudioConnection> patchCordKST_FX;
    std::unique_ptr<AudioConnection> patchCordHCC_FX;
    std::unique_ptr<AudioConnection> patchCordFX_Out;
    std::unique_ptr<AudioConnection> patchCordFX_Reverb;
    std::unique_ptr<AudioConnection> patchCordReverb_Out;
    std::unique_ptr<AudioConnection> patchCordOut_AudioOutR;
    std::unique_ptr<AudioConnection> patchCordOut_AudioOutL;

    uint32_t lastTriggerTime = 0; // Used to trigger drum sound periodically

    int sixteenthNote = 125000;

};

#endif
