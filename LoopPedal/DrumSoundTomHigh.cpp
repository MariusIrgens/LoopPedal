#include "DrumSoundTomHigh.h"

DrumSoundTomHigh::DrumSoundTomHigh(int mixerChannel, AudioMixer4& mixer)
    : DrumSound(mixerChannel, mixer)
{
    patchCordTriangleOsc_Mix = std::make_unique<AudioConnection>(triangleOsc, 0, oscMixer, 0);
    patchCordMix_Bit = std::make_unique<AudioConnection>(oscMixer, 0, bitCrusher, 0);
    patchCordBit_Out = std::make_unique<AudioConnection>(bitCrusher, 0, mixer, mixerChannel);

    // Set all base values
    oscMixer.gain(0, 1.0f);
    oscMixer.gain(1, 1.0f);
    oscMixer.gain(2, 1.0f);
    oscMixer.gain(3, 0.0f);
    triangleOsc.begin(3);
    triangleOsc.amplitude(0.0);
    triangleOsc.frequency(maxFreqTriangleOsc);
    bitCrusher.bits(16);
    bitCrusher.sampleRate(44100);

    envelopeTriangleOscAmplitude = std::make_unique<Envelope>(maxAmplitudeTriangleOsc, minAmplitudeTriangleOsc, attackTimeAmplitudeTriangleOsc, decayTimeAmplitudeTriangleOsc, curvednessAmplitudeTriangleOsc);
    envelopeTriangleOscFreq = std::make_unique<Envelope>(maxFreqTriangleOsc, minFreqTriangleOsc, attackTimeFreqTriangleOsc, decayTimeFreqTriangleOsc, curvednessFreqTriangleOsc);

}

void DrumSoundTomHigh::trigger(int velocity)
{
    envelopes_restarted = true;
    envelopeTriangleOscAmplitude->start();
    envelopeTriangleOscFreq->start();

    if (debugMode) {
        Serial.println("High tom sound");
    }
}

void DrumSoundTomHigh::update(int deltaTime)
{
    if (envelopes_restarted)
    {
        envelopeTriangleOscAmplitude->update(deltaTime);
        triangleOsc.amplitude(envelopeTriangleOscAmplitude->read());
        envelopeTriangleOscFreq->update(deltaTime);
        triangleOsc.frequency(envelopeTriangleOscFreq->read());
    }
}

void DrumSoundTomHigh::choke()
{
    triangleOsc.amplitude(0.0f);
    envelopes_restarted = false;
}

void DrumSoundTomHigh::newDrum()
{
    choke();

    // Settings
    // Triangle Osc
    maxAmplitudeTriangleOsc = randomFloat(0.35f, 0.5f);
    minAmplitudeTriangleOsc = 0.0f;
    attackTimeAmplitudeTriangleOsc = randomFloat(0.5f, 1.0f) * 10.0f;
    decayTimeAmplitudeTriangleOsc = randomFloat(0.5f, 1.0f) * 500.0f;
    curvednessAmplitudeTriangleOsc = randomFloat(0.1f, 0.5f);

    maxFreqTriangleOsc = randomFloat(0.25f, 1.0f) * 800.0f;
    minFreqTriangleOsc = randomFloat(0.2f, 0.9f) * maxFreqTriangleOsc;
    attackTimeFreqTriangleOsc = randomFloat(0.5f, 1.0f) * 10.0f;
    decayTimeFreqTriangleOsc = randomFloat(0.5f, 1.0f) * 500.0f;
    curvednessFreqTriangleOsc = randomFloat(0.1f, 0.5f);

    triangleOsc.begin(random(0, 8));

    // FX
    bitCrusher.bits(random(4, 16));
    bitCrusher.sampleRate(random(5512, 44100));

    envelopeTriangleOscAmplitude = std::make_unique<Envelope>(maxAmplitudeTriangleOsc, minAmplitudeTriangleOsc, attackTimeAmplitudeTriangleOsc, decayTimeAmplitudeTriangleOsc, curvednessAmplitudeTriangleOsc);
    envelopeTriangleOscFreq = std::make_unique<Envelope>(maxFreqTriangleOsc, minFreqTriangleOsc, attackTimeFreqTriangleOsc, decayTimeFreqTriangleOsc, curvednessFreqTriangleOsc);

}