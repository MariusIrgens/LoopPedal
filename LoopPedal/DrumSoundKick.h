#ifndef _DRUMSOUNDKICK_h
#define _DRUMSOUNDKICK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "DrumSound.h"
#include "Envelope.h"

class DrumSoundKick : public DrumSound {
public:
	DrumSoundKick(int mixerChannel, AudioMixer4& mixer);
    void trigger(int velocity) override;  // Overriding the base class trigger method
	void update(int deltaTime) override;

private:
	AudioSynthWaveformSine sineOsc;
	AudioConnection patchCord;
	Envelope envelopeFreq;
};

#endif