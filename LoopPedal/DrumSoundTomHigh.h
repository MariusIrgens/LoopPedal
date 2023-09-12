// DrumSoundTomHigh.h

#ifndef _DRUMSOUNDTOMHIGH_h
#define _DRUMSOUNDTOMHIGH_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#pragma once
#include <memory>
#include "DrumSound.h"
#include "Envelope.h"

class DrumSoundTomHigh : public DrumSound
{
public:
	DrumSoundTomHigh(int mixerChannel, AudioMixer4& mixer);
	void trigger(int velocity) override;
	void update(int deltaTime) override;

private:
	// Modules
	AudioSynthWaveform triangleOsc;
	AudioMixer4 oscMixer;

	// Patching
	std::unique_ptr<AudioConnection> patchCordTriangleOsc_Mix;
	std::unique_ptr<AudioConnection> patchCordMix_Out;

	// Envelopes
	bool envelopes_restarted = false;
	std::unique_ptr<Envelope> envelopeTriangleOscAmplitude;
	std::unique_ptr<Envelope> envelopeTriangleOscFreq;

	// Settings
	// Triangle Osc
	float maxAmplitudeTriangleOsc = 0.5f;
	float minAmplitudeTriangleOsc = 0.0f;
	float attackTimeAmplitudeTriangleOsc = 5.0f;
	float decayTimeAmplitudeTriangleOsc = 250.0f;
	float curvednessAmplitudeTriangleOsc = 0.2f;

	float maxFreqTriangleOsc = 800.0;
	float minFreqTriangleOsc = 400.0f;
	float attackTimeFreqTriangleOsc = 5.0f;
	float decayTimeFreqTriangleOsc = 350.0f;
	float curvednessFreqTriangleOsc = 0.7f;


};

#endif

