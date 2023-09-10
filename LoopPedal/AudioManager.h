#ifndef _AUDIOMANAGER_h
#define _AUDIOMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <Audio.h>
#include "Sequencer.h"

class AudioManager {
public:
    AudioManager();
    void setup();
    void loop();
    static void drumPatternISR();

private:
    static AudioManager* instance;
    //Sequencer sequencer;
    IntervalTimer drumTimer;

    AudioControlSGTL5000 sgtl5000; // SGTL5000 audio codec control object
    AudioInputI2S audioInput; // Stereo audio input
    AudioAmplifier amplifier; // Amplifier for volume boost
    AudioOutputI2S audioOutput; // Stereo audio output
    AudioSynthSimpleDrum drum; // Simple drum sound synthesis
    AudioMixer4 mixer1;
    AudioMixer4 mixer2; 
    AudioMixer4 mixer3;

    AudioConnection patchCord1;
    AudioConnection patchCord2;
    AudioConnection patchCord3;
    AudioConnection patchCord4;
    AudioConnection patchCord5;
    AudioConnection patchCord6;

    uint32_t lastTriggerTime = 0; // Used to trigger drum sound periodically

    DrumSound kick;

};

#endif
