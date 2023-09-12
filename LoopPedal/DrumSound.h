// DrumSound.h

#ifndef _DRUMSOUND_h
#define _DRUMSOUND_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#pragma once
#include <Audio.h>

class DrumSound {
public:
    DrumSound(int mixerChannel, AudioMixer4& mixer);
    virtual ~DrumSound() = default;
    virtual void trigger(int velocity);
    virtual void update(int resolution);
    virtual void choke();

protected:
    bool debugMode = true;
};

#endif

