#include "DrumSoundSnare.h"

DrumSoundSnare::DrumSoundSnare(int mixerChannel, AudioMixer4& mixer)
    : DrumSound(mixerChannel, mixer)
{
    // Patch up
    patchCordNoise_Filter = std::make_unique<AudioConnection>(noise, 0, noiseFilter, 0);
    patchCordFilter_Mix = std::make_unique<AudioConnection>(noiseFilter, 0, oscMixer, 0);
    patchCordTriangleOsc_Mix = std::make_unique<AudioConnection>(triangleOsc, 0, oscMixer, 1);
    patchCordMix_Out = std::make_unique<AudioConnection>(oscMixer, 0, mixer, mixerChannel);

    patchCordTriangleMod_TriangleOsc = std::make_unique<AudioConnection>(triangleMod, 0, triangleOsc, 0);

    // Set all base values
    oscMixer.gain(0, 1.0f);
    oscMixer.gain(1, 1.0f);
    oscMixer.gain(2, 0.0f);
    oscMixer.gain(3, 0.0f);
    triangleOsc.begin(3);
    triangleOsc.amplitude(0.0);
    triangleOsc.frequency(maxFreqTriangleOsc);

    newDrum();

}

void DrumSoundSnare::trigger(int velocity) {

    envelopes_restarted = true;
    envelopeNoiseAmplitude->start();
    envelopeNoiseFilterFreq->start();
    envelopeTriangleOscAmplitude->start();
    envelopeTriangleOscFreq->start();

    if (debugMode) {
        Serial.println("Snare sound");
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

void DrumSoundSnare::choke()
{
    noise.amplitude(0.0f);
    triangleOsc.amplitude(0.0f);
    noiseFilter.frequency(0.0f);
    envelopes_restarted = false;
}

void DrumSoundSnare::newDrum()
{
    choke();

    // Settings
    
    // Noise 
    maxAmplitudeNoise = randomFloat(0.75f, 1.0f);
    minAmplitudeNoise = 0.0f;
    attackTimeAmplitudeNoise = randomFloat(0.5f, 1.0f) * 10.0f;
    decayTimeAmplitudeNoise = randomFloat(0.35f, 1.0f) * 700.0f;
    curvednessAmplitudeNoise = randomFloat(0.5f, 1.0f);

    maxFilterFreqNoise = randomFloat(0.5f, 1.0f) * 6000.0f;
    minFilterFreqNoise = randomFloat(0.5f, 1.0f) * 600.0f;
    attackTimeFilterFreqNoise = randomFloat(0.5f, 1.0f) * 10.0f;
    decayTimeFilterFreqNoise = randomFloat(0.5f, 1.0f) * 300.0f;
    curvednessFilterFreqNoise = randomFloat(0.1f, 0.5f);

    // Triangle Osc
    maxAmplitudeTriangleOsc = randomFloat(0.5f, 1.0f) * 0.4f;
    minAmplitudeTriangleOsc = 0.0f;
    attackTimeAmplitudeTriangleOsc = randomFloat(0.5f, 1.0f) * 10.0f;
    decayTimeAmplitudeTriangleOsc = randomFloat(0.5f, 1.0f) * decayTimeAmplitudeNoise;
    curvednessAmplitudeTriangleOsc = randomFloat(0.5f, 1.0f);

    maxFreqTriangleOsc = randomFloat(0.25f, 1.0f) * 650.0f;
    minFreqTriangleOsc = randomFloat(0.25f, 0.75f) * maxFreqTriangleOsc;
    attackTimeFreqTriangleOsc = randomFloat(0.5f, 1.0f) * 10.0f;
    decayTimeFreqTriangleOsc = randomFloat(0.5f, 1.0f) * 450.0f;
    curvednessFreqTriangleOsc = randomFloat(0.5f, 1.0f);

    // Triangle Modulation
    triangleMod.begin(randomFloat(0.0f, 0.1f), randomFloat(0.0f, 1.0f) * 500.0f, random(0, 8));

    // Redefine all envelopes
    envelopeNoiseAmplitude = std::make_unique<Envelope>(maxAmplitudeNoise, minAmplitudeNoise, attackTimeAmplitudeNoise, decayTimeAmplitudeNoise, curvednessAmplitudeNoise);
    envelopeNoiseFilterFreq = std::make_unique<Envelope>(maxFilterFreqNoise, minFilterFreqNoise, attackTimeFilterFreqNoise, decayTimeFilterFreqNoise, curvednessFilterFreqNoise);
    envelopeTriangleOscAmplitude = std::make_unique<Envelope>(maxAmplitudeTriangleOsc, minAmplitudeTriangleOsc, attackTimeAmplitudeTriangleOsc, decayTimeAmplitudeTriangleOsc, curvednessAmplitudeTriangleOsc);
    envelopeTriangleOscFreq = std::make_unique<Envelope>(maxFreqTriangleOsc, minFreqTriangleOsc, attackTimeFreqTriangleOsc, decayTimeFreqTriangleOsc, curvednessFreqTriangleOsc);

}