#ifndef _DRUMSOUNDKICK_h
#define _DRUMSOUNDKICK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#pragma once
#include <memory>
#include "DrumSound.h"
#include "Envelope.h"

class DrumSoundKick : public DrumSound {
public:
	DrumSoundKick(int mixerChannel, AudioMixer4& mixer);
    void trigger(int velocity) override;
	void update(int deltaTime) override;
	void choke() override;
	void newDrum() override;

private:
	// Modules
	AudioSynthWaveformSine sineOsc;
	AudioSynthWaveformSine clickOsc;
	AudioSynthNoiseWhite noise;
	AudioFilterStateVariable noiseFilter;
	AudioMixer4 oscMixer;
	AudioEffectBitcrusher bitCrusher;

	// Patching
	std::unique_ptr<AudioConnection> patchCordSine_Mix;
	std::unique_ptr<AudioConnection> patchCordClick_Mix;
	std::unique_ptr<AudioConnection> patchCordNoise_Filter;
	std::unique_ptr<AudioConnection> patchCordFilter_Mix;
	std::unique_ptr<AudioConnection> patchCordMix_Bit;
	std::unique_ptr<AudioConnection> patchCordBit_Out;

	// Envelopes
	bool envelopes_restarted = false;
	std::unique_ptr<Envelope> envelopeSineAmplitude;
	std::unique_ptr<Envelope> envelopeSineFrequency;
	std::unique_ptr<Envelope> envelopeClickAmplitude;
	std::unique_ptr<Envelope> envelopeClickFrequency;
	std::unique_ptr<Envelope> envelopeNoiseAmplitude;


	// Settings
	// Sine Oscillator
	float maxAmplitudeSine = 1.0f;
	float minAmplitudeSine = 0.0f;
	float attackTimeAmplitudeSine = 5.0f;
	float decayTimeAmplitudeSine = 500.0f;
	float curvednessAmplitudeSine = 0.1f;

	float maxFrequencySine = 350.0f;
	float minFrequencySine = 20.0f;
	float attackTimeFrequencySine = 5.0f;
	float decayTimeFrequencySine = 200.0f;
	float curvednessFrequencySine = 0.1f;

	// Click Oscillator
	float maxAmplitudeClick = 0.2f;
	float minAmplitudeClick = 0.0f;
	float attackTimeAmplitudeClick = 5.0f;
	float decayTimeAmplitudeClick = 50.0f;
	float curvednessAmplitudeClick = 0.5f;

	float maxFrequencyClick = 700.0f;
	float minFrequencyClick = 20.0f;
	float attackTimeFrequencyClick = 5.0f;
	float decayTimeFrequencyClick = 25.0f;
	float curvednessFrequencyClick = 0.1f;

	// Noise
	float maxAmplitudeNoise = 0.5f;
	float minAmplitudeNoise = 0.0f;
	float attackTimeAmplitudeNoise = 5.0f;
	float decayTimeAmplitudeNoise = 50.0f;
	float curvednessAmplitudeNoise = 0.1f;

	float noiseFilterFrequency = 2000.0f;
};

#endif