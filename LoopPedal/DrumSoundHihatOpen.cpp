#include "DrumSoundHihatOpen.h"

DrumSoundHihatOpen::DrumSoundHihatOpen(int mixerChannel, AudioMixer4& mixer)
    : DrumSound(mixerChannel, mixer)
{
    patchCordNoise_Filter = std::make_unique<AudioConnection>(noise, 0, noiseFilter, 0);
    patchCordFilter_Mix = std::make_unique<AudioConnection>(noiseFilter, 0, oscMixer, 0);
    patchCordMix_Out = std::make_unique<AudioConnection>(oscMixer, 0, mixer, mixerChannel);

    // Set all base values
    oscMixer.gain(0, 1.0f);
    oscMixer.gain(1, 0.0f);
    oscMixer.gain(2, 0.0f);
    oscMixer.gain(3, 0.0f);

    envelopeNoiseAmplitude = std::make_unique<Envelope>(maxAmplitudeNoise, minAmplitudeNoise, attackTimeAmplitudeNoise, decayTimeAmplitudeNoise, curvednessAmplitudeNoise);
    envelopeNoiseFilterFreq = std::make_unique<Envelope>(maxFilterFreqNoise, minFilterFreqNoise, attackTimeFilterFreqNoise, decayTimeFilterFreqNoise, curvednessFilterFreqNoise);

}

void DrumSoundHihatOpen::trigger(int velocity) {

    envelopes_restarted = true;
    envelopeNoiseAmplitude->start();
    envelopeNoiseFilterFreq->start();

    if (debugMode) {
        //Serial.print("Hihat sound");
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
    noise.amplitude(minAmplitudeNoise);
    noiseFilter.frequency(minFilterFreqNoise);
    envelopes_restarted = false;
}
