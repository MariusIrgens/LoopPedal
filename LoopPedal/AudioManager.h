#ifndef _AUDIOMANAGER_h
#define _AUDIOMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Audio.h>

class AudioManager {
public:
    AudioManager();
    void setup();
    void loop();

private:
    AudioControlSGTL5000 sgtl5000; // SGTL5000 audio codec control object
    AudioInputI2S audioInput; // Stereo audio input
    AudioAmplifier amplifier; // Amplifier for volume boost
    AudioOutputI2S audioOutput; // Stereo audio output

    AudioConnection patchCord1;
    AudioConnection patchCord3;

};

#endif

