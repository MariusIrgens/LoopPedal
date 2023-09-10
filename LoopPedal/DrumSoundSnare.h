// DrumSoundSnare.h

#ifndef _DRUMSOUNDSNARE_h
#define _DRUMSOUNDSNARE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "DrumSound.h"

class DrumSoundSnare : public DrumSound {
public:
	DrumSoundSnare(int mixerChannel, AudioMixer4& mixer);
	void trigger(int velocity) override;  // Overriding the base class trigger method

private:
	AudioSynthSimpleDrum drumSynth;
	AudioConnection patchCord;

};

#endif

