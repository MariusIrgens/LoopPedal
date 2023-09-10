// DrumSound.h

#ifndef _DRUMSOUND_h
#define _DRUMSOUND_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#pragma once
#include <Audio.h>  // Include the Teensy Audio library

class DrumSound {
public:
    DrumSound(int mixerChannel, AudioMixer4& mixer);
    void trigger();

private:
    AudioSynthSimpleDrum drumSynth;
    AudioConnection patchCord;
    bool debugMode = true;
};

#endif

