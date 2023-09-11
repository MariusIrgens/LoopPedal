#include "DrumSoundKick.h"

DrumSoundKick::DrumSoundKick(int mixerChannel, AudioMixer4& mixer)
    : DrumSound(mixerChannel, mixer)
{
    patchCordSineMix = std::make_unique<AudioConnection>(sineOsc, 0, synthMixer, 0);
    patchCordClickMix = std::make_unique<AudioConnection>(clickOsc, 0, synthMixer, 1);
    patchCordNoiseFilter = std::make_unique<AudioConnection>(noise, 0, noiseFilter, 0);
    patchCordFilterMix = std::make_unique<AudioConnection>(noiseFilter, 0, synthMixer, 2);
    patchCordOut = std::make_unique<AudioConnection>(synthMixer, 0, mixer, mixerChannel);

    // Set all base values
    synthMixer.gain(0, 1.0f);
    synthMixer.gain(1, 1.0f);
    synthMixer.gain(2, 1.0f);
    synthMixer.gain(3, 0.0f);

    sineOsc.frequency(maxFrequencySine);
    clickOsc.frequency(maxFrequencyClick);
    noiseFilter.frequency(noiseFilterFrequency);
    noise.amplitude(1.0f);

    // Define all envelopes
    envelopeSineAmplitude = std::make_unique<Envelope>(maxAmplitudeSine, minAmplitudeSine, attackTimeAmplitudeSine, decayTimeAmplitudeSine, curvednessAmplitudeSine);
    envelopeSineFrequency = std::make_unique<Envelope>(maxFrequencySine, minFrequencySine, attackTimeFrequencySine, decayTimeFrequencySine, curvednessFrequencySine);
    envelopeClickAmplitude = std::make_unique<Envelope>(maxAmplitudeClick, minAmplitudeClick, attackTimeAmplitudeClick, decayTimeAmplitudeClick, curvednessAmplitudeClick);
    envelopeClickFrequency = std::make_unique<Envelope>(maxFrequencyClick, minFrequencyClick, attackTimeFrequencyClick, decayTimeFrequencyClick, curvednessFrequencyClick);
    envelopeNoiseAmplitude = std::make_unique<Envelope>(maxAmplitudeNoise, minAmplitudeNoise, attackTimeAmplitudeNoise, decayTimeAmplitudeNoise, curvednessAmplitudeNoise);
}

void DrumSoundKick::trigger(int velocity) {
    // Set all velocity sensitive parameters
    //envelopeSineFrequency.setCurvedness(float(velocity) / 10.0f);

    // Start all envelopes
    envelopeSineAmplitude->start();
    envelopeSineFrequency->start();
    envelopeClickAmplitude->start();
    envelopeClickFrequency->start();
    envelopeNoiseAmplitude->start();

    if (debugMode) {
        //Serial.print("is Active");
        //Serial.print(synthMixer.isActive());
    }
}

void DrumSoundKick::update(int deltaTime) {

    envelopeSineAmplitude->update(deltaTime);
    sineOsc.amplitude(envelopeSineAmplitude->read());
    envelopeSineFrequency->update(deltaTime);
    sineOsc.frequency(envelopeSineFrequency->read());

    envelopeClickAmplitude->update(deltaTime);
    clickOsc.amplitude(envelopeClickAmplitude->read());
    envelopeClickFrequency->update(deltaTime);
    clickOsc.frequency(envelopeClickFrequency->read());

    envelopeNoiseAmplitude->update(deltaTime);
    noise.amplitude(envelopeNoiseAmplitude->read());

}