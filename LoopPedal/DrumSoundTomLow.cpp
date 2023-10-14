#include "DrumSoundTomLow.h"

DrumSoundTomLow::DrumSoundTomLow(int mixerChannel, AudioMixer4& mixer)
    : DrumSound(mixerChannel, mixer)
{
    patchCordTriangleOsc_Mix = std::make_unique<AudioConnection>(triangleOsc, 0, oscMixer, 0);
    patchCordMix_Out = std::make_unique<AudioConnection>(oscMixer, 0, mixer, mixerChannel);

    // Set all base values
    oscMixer.gain(0, 1.0f);
    oscMixer.gain(1, 1.0f);
    oscMixer.gain(2, 1.0f);
    oscMixer.gain(3, 0.0f);
    triangleOsc.begin(3);
    triangleOsc.amplitude(0.0);
    triangleOsc.frequency(maxFreqTriangleOsc);

    envelopeTriangleOscAmplitude = std::make_unique<Envelope>(maxAmplitudeTriangleOsc, minAmplitudeTriangleOsc, attackTimeAmplitudeTriangleOsc, decayTimeAmplitudeTriangleOsc, curvednessAmplitudeTriangleOsc);
    envelopeTriangleOscFreq = std::make_unique<Envelope>(maxFreqTriangleOsc, minFreqTriangleOsc, attackTimeFreqTriangleOsc, decayTimeFreqTriangleOsc, curvednessFreqTriangleOsc);

}

void DrumSoundTomLow::trigger(int velocity)
{
    envelopes_restarted = true;
    envelopeTriangleOscAmplitude->start();
    envelopeTriangleOscFreq->start();

    if (debugMode) {
        Serial.println("Low tom sound");
    }
}

void DrumSoundTomLow::update(int deltaTime)
{
    if (envelopes_restarted)
    {
        envelopeTriangleOscAmplitude->update(deltaTime);
        triangleOsc.amplitude(envelopeTriangleOscAmplitude->read());
        envelopeTriangleOscFreq->update(deltaTime);
        triangleOsc.frequency(envelopeTriangleOscFreq->read());
    }
}

