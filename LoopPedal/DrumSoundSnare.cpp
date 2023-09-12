#include "DrumSoundSnare.h"

DrumSoundSnare::DrumSoundSnare(int mixerChannel, AudioMixer4& mixer)
    : DrumSound(mixerChannel, mixer)
{
    // Patch up
    patchCordNoise_Filter = std::make_unique<AudioConnection>(noise, 0, noiseFilter, 0);
    patchCordFilter_Mix = std::make_unique<AudioConnection>(noiseFilter, 0, oscMixer, 0);
    patchCordTriangleOsc_Mix = std::make_unique<AudioConnection>(triangleOsc, 0, oscMixer, 1);
    patchCordMix_Out = std::make_unique<AudioConnection>(oscMixer, 0, mixer, mixerChannel);

    // Set all base values
    oscMixer.gain(0, 1.0f);
    oscMixer.gain(1, 1.0f);
    oscMixer.gain(2, 0.0f);
    oscMixer.gain(3, 0.0f);
    triangleOsc.begin(3);
    triangleOsc.amplitude(0.0);
    triangleOsc.frequency(maxFreqTriangleOsc);

    // Define all envelopes
    envelopeNoiseAmplitude = std::make_unique<Envelope>(maxAmplitudeNoise, minAmplitudeNoise, attackTimeAmplitudeNoise, decayTimeAmplitudeNoise, curvednessAmplitudeNoise);
    envelopeNoiseFilterFreq = std::make_unique<Envelope>(maxFilterFreqNoise, minFilterFreqNoise, attackTimeFilterFreqNoise, decayTimeFilterFreqNoise, curvednessFilterFreqNoise);
    envelopeTriangleOscAmplitude = std::make_unique<Envelope>(maxAmplitudeTriangleOsc, minAmplitudeTriangleOsc, attackTimeAmplitudeTriangleOsc, decayTimeAmplitudeTriangleOsc, curvednessAmplitudeTriangleOsc);
    envelopeTriangleOscFreq = std::make_unique<Envelope>(maxFreqTriangleOsc, minFreqTriangleOsc, attackTimeFreqTriangleOsc, decayTimeFreqTriangleOsc, curvednessFreqTriangleOsc);

}

void DrumSoundSnare::trigger(int velocity) {

    envelopes_restarted = true;
    envelopeNoiseAmplitude->start();
    envelopeNoiseFilterFreq->start();
    envelopeTriangleOscAmplitude->start();
    envelopeTriangleOscFreq->start();

    if (debugMode) {
        //Serial.print("Snare sound");
    }
}

void DrumSoundSnare::update(int deltaTime)
{
    if (envelopes_restarted)
    {
        envelopeNoiseAmplitude->update(deltaTime);
        noise.amplitude(envelopeNoiseAmplitude->read());
        envelopeNoiseFilterFreq->update(deltaTime);
        noiseFilter.frequency(envelopeNoiseFilterFreq->read());

        envelopeTriangleOscAmplitude->update(deltaTime);
        triangleOsc.amplitude(envelopeTriangleOscAmplitude->read());
        envelopeTriangleOscFreq->update(deltaTime);
        triangleOsc.frequency(envelopeTriangleOscFreq->read());
    }

}