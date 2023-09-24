// DrumSoundHihatOpen.h

#ifndef _DRUMSOUNDHIHATOPEN_h
#define _DRUMSOUNDHIHATOPEN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#pragma once
#include <memory>
#include "DrumSound.h"
#include "Envelope.h"

class DrumSoundHihatOpen : public DrumSound
{
public:
	DrumSoundHihatOpen(int mixerChannel, AudioMixer4& mixer);
	void trigger(int velocity) override;
	void update(int deltaTime) override;
	void choke() override;

private:

	// Modules
	AudioSynthNoiseWhite noise;
	AudioFilterStateVariable noiseFilter;
	AudioMixer4 oscMixer;

	// Patchings
	std::unique_ptr<AudioConnection> patchCordNoise_Filter;
	std::unique_ptr<AudioConnection> patchCordFilter_Mix;
	std::unique_ptr<AudioConnection> patchCordMix_Out;

	// Envelopes
	bool envelopes_restarted = false;
	std::unique_ptr<Envelope> envelopeNoiseAmplitude;
	std::unique_ptr<Envelope> envelopeNoiseFilterFreq;

	// Settings
	// Noise 
	float maxAmplitudeNoise = 0.5f;
	float minAmplitudeNoise = 0.0f;
	float attackTimeAmplitudeNoise = 5.0f;
	float decayTimeAmplitudeNoise = 500.0f;
	float curvednessAmplitudeNoise = 0.1f;

	float maxFilterFreqNoise = 8000.0;
	float minFilterFreqNoise = 4000.0f;
	float attackTimeFilterFreqNoise = 5.0f;
	float decayTimeFilterFreqNoise = 250.0f;
	float curvednessFilterFreqNoise = 0.1f;
};

#endif
