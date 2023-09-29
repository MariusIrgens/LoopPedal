// DrumSoundSnare.h

#ifndef _DRUMSOUNDSNARE_h
#define _DRUMSOUNDSNARE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#pragma once
#include <memory>
#include "DrumSound.h"
#include "Envelope.h"

class DrumSoundSnare : public DrumSound {
public:
	DrumSoundSnare(int mixerChannel, AudioMixer4& mixer);
	void trigger(int velocity) override;
	void update(int deltaTime) override;
	void choke() override;
	void newDrum() override;
private:

	// Modules
	AudioSynthNoiseWhite noise;
	AudioSynthWaveform triangleOsc;
	AudioFilterStateVariable noiseFilter;
	AudioMixer4 oscMixer;


	// Patchings
	std::unique_ptr<AudioConnection> patchCordNoise_Filter;
	std::unique_ptr<AudioConnection> patchCordFilter_Mix;
	std::unique_ptr<AudioConnection> patchCordTriangleOsc_Mix;
	std::unique_ptr<AudioConnection> patchCordMix_Out;

	// Envelopes
	bool envelopes_restarted = false;
	std::unique_ptr<Envelope> envelopeNoiseAmplitude;
	std::unique_ptr<Envelope> envelopeNoiseFilterFreq;
	std::unique_ptr<Envelope> envelopeTriangleOscAmplitude;
	std::unique_ptr<Envelope> envelopeTriangleOscFreq;


	// Settings
	// Noise 
	float maxAmplitudeNoise = 1.0f;
	float minAmplitudeNoise = 0.0f;
	float attackTimeAmplitudeNoise = 5.0f;
	float decayTimeAmplitudeNoise = 500.0f;
	float curvednessAmplitudeNoise = 1.0f;

	float maxFilterFreqNoise = 4500.0;
	float minFilterFreqNoise = 450.0f;
	float attackTimeFilterFreqNoise = 5.0f;
	float decayTimeFilterFreqNoise = 200.0f;
	float curvednessFilterFreqNoise = 0.1f;

	// Triangle Osc
	float maxAmplitudeTriangleOsc = 0.5f;
	float minAmplitudeTriangleOsc = 0.0f;
	float attackTimeAmplitudeTriangleOsc = 5.0f;
	float decayTimeAmplitudeTriangleOsc = 500.0f;
	float curvednessAmplitudeTriangleOsc = 1.0f;

	float maxFreqTriangleOsc = 300.0;
	float minFreqTriangleOsc = 100.0f;
	float attackTimeFreqTriangleOsc = 5.0f;
	float decayTimeFreqTriangleOsc = 350.0f;
	float curvednessFreqTriangleOsc = 1.0f;
};

#endif

