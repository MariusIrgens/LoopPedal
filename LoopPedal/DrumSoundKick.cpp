#include "DrumSoundKick.h"

DrumSoundKick::DrumSoundKick(int mixerChannel, AudioMixer4& mixer)
    : DrumSound(mixerChannel, mixer)
{
    // Patch up
    patchCordSine_Mix = std::make_unique<AudioConnection>(sineOsc, 0, oscMixer, 0);
    patchCordClick_Mix = std::make_unique<AudioConnection>(clickOsc, 0, oscMixer, 1);
    patchCordNoise_Filter = std::make_unique<AudioConnection>(noise, 0, noiseFilter, 0);
    patchCordFilter_Mix = std::make_unique<AudioConnection>(noiseFilter, 0, oscMixer, 2);
    patchCordMix_Out = std::make_unique<AudioConnection>(oscMixer, 0, mixer, mixerChannel);

    // Set all base values
    oscMixer.gain(0, 1.0f);
    oscMixer.gain(1, 1.0f);
    oscMixer.gain(2, 1.0f);
    oscMixer.gain(3, 0.0f);
    sineOsc.frequency(maxFrequencySine);
    sineOsc.amplitude(0.0f);
    clickOsc.frequency(maxFrequencyClick);
    clickOsc.amplitude(0.0f);
    noiseFilter.frequency(noiseFilterFrequency);
    noise.amplitude(0.0f);

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
    envelopes_restarted = true;
    envelopeSineAmplitude->start();
    envelopeSineFrequency->start();
    envelopeClickAmplitude->start();
    envelopeClickFrequency->start();
    envelopeNoiseAmplitude->start();

    if (debugMode) {
        //Serial.print("is Active");
    }
}

void DrumSoundKick::update(int deltaTime) {
    if (envelopes_restarted)
    {
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


}