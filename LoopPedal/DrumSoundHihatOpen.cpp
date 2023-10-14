#include "DrumSoundHihatOpen.h"

DrumSoundHihatOpen::DrumSoundHihatOpen(int mixerChannel, AudioMixer4& mixer)
    : DrumSound(mixerChannel, mixer)
{
    patchCordNoise_Filter = std::make_unique<AudioConnection>(noise, 0, noiseFilter, 0);
    patchCordFilter_Mix = std::make_unique<AudioConnection>(noiseFilter, 0, oscMixer, 0);
    patchCordMix_EQ = std::make_unique<AudioConnection>(oscMixer, 0, EQFilter, 0);
    patchCordEQ_Out = std::make_unique<AudioConnection>(EQFilter, 2, mixer, mixerChannel);

    // Set all base values
    oscMixer.gain(0, 1.0f);
    oscMixer.gain(1, 0.0f);
    oscMixer.gain(2, 0.0f);
    oscMixer.gain(3, 0.0f);

    newDrum();

}

void DrumSoundHihatOpen::trigger(int velocity) {

    envelopes_restarted = true;
    envelopeNoiseAmplitude->start();
    envelopeNoiseFilterFreq->start();

    if (debugMode) {
        Serial.println("Open hihat sound");
    }
}

void DrumSoundHihatOpen::update(int deltaTime)
{
    if (envelopes_restarted)
    {
        envelopeNoiseAmplitude->update(deltaTime);
        noise.amplitude(envelopeNoiseAmplitude->read());
        envelopeNoiseFilterFreq->update(deltaTime);
        noiseFilter.frequency(envelopeNoiseFilterFreq->read());
    }
}

void DrumSoundHihatOpen::choke()
{
    noise.amplitude(0.0f);
    noiseFilter.frequency(0.0f);
    envelopes_restarted = false;
}

void DrumSoundHihatOpen::newDrum()
{
    choke();

    // Settings

    // Noise 
    maxAmplitudeNoise = randomFloat(0.3f, 0.5f);
    minAmplitudeNoise = 0.0f;
    attackTimeAmplitudeNoise = randomFloat(0.5f, 1.0f) * 10.0f;
    decayTimeAmplitudeNoise = randomFloat(0.5f, 1.0f) * 500.0f;
    curvednessAmplitudeNoise = randomFloat(0.1f, 0.5f);

    maxFilterFreqNoise = randomFloat(0.5f, 1.0f) * 10000.0;
    minFilterFreqNoise = randomFloat(0.5f, 1.0f) * 5000.0f;
    attackTimeFilterFreqNoise = randomFloat(0.5f, 1.0f) * 10.0f;
    decayTimeFilterFreqNoise = randomFloat(0.5f, 1.0f) * 250.0f;
    curvednessFilterFreqNoise = randomFloat(0.1f, 0.5f);

    // High Pass Filter
    EQFilter.frequency(randomFloat(0.75f, 1.0f) * 3500.0f);

    envelopeNoiseAmplitude = std::make_unique<Envelope>(maxAmplitudeNoise, minAmplitudeNoise, attackTimeAmplitudeNoise, decayTimeAmplitudeNoise, curvednessAmplitudeNoise);
    envelopeNoiseFilterFreq = std::make_unique<Envelope>(maxFilterFreqNoise, minFilterFreqNoise, attackTimeFilterFreqNoise, decayTimeFilterFreqNoise, curvednessFilterFreqNoise);

}
