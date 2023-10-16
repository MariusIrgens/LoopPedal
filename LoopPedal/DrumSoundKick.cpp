#include "DrumSoundKick.h"

DrumSoundKick::DrumSoundKick(int mixerChannel, AudioMixer4& mixer)
    : DrumSound(mixerChannel, mixer)
{
    // Patch up
    patchCordSine_Mix = std::make_unique<AudioConnection>(sineOsc, 0, oscMixer, 0);
    patchCordClick_Mix = std::make_unique<AudioConnection>(clickOsc, 0, oscMixer, 1);
    patchCordNoise_Filter = std::make_unique<AudioConnection>(noise, 0, noiseFilter, 0);
    patchCordFilter_Mix = std::make_unique<AudioConnection>(noiseFilter, 0, oscMixer, 2);
    patchCordMix_Bit = std::make_unique<AudioConnection>(oscMixer, 0, bitCrusher, 0);
    patchCordBit_Out = std::make_unique<AudioConnection>(bitCrusher, 0, mixer, mixerChannel);

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
    bitCrusher.bits(16);
    bitCrusher.sampleRate(44100);

    newDrum();
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
        Serial.println("Kick sound");
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

void DrumSoundKick::choke()
{
    sineOsc.amplitude(0.0f);
    clickOsc.amplitude(0.0f);
    noise.amplitude(0.0f);
    noiseFilter.frequency(0.0f);
    envelopes_restarted = false;
}


void DrumSoundKick::newDrum()
{
    choke();

    // Settings
    
    // Sine Oscillator
    maxAmplitudeSine = randomFloat(0.7f, 1.0f);
    minAmplitudeSine = 0.0f;
    attackTimeAmplitudeSine = randomFloat(0.5f, 1.0f) * 10.0f;
    decayTimeAmplitudeSine = randomFloat(0.2f, 1.0f) * 800.0f;
    curvednessAmplitudeSine = randomFloat(0.1f, 0.5f);

    maxFrequencySine = randomFloat(0.75f, 1.0f) * 350.0f;
    minFrequencySine = randomFloat(0.25f, 1.0f) * 40.0f;
    attackTimeFrequencySine = randomFloat(0.5f, 1.0f) * 10.0f;
    decayTimeFrequencySine = randomFloat(0.2f, 1.0f) * 600.0f;
    curvednessFrequencySine = randomFloat(0.1f, 0.5f);

    // Click Oscillator
    maxAmplitudeClick = randomFloat(0.5f, 1.0f) * 0.4f;
    minAmplitudeClick = 0.0f;
    attackTimeAmplitudeClick = randomFloat(0.5f, 1.0f) * 5.0f;
    decayTimeAmplitudeClick = randomFloat(0.5f, 1.0f) * 75.0f;
    curvednessAmplitudeClick = randomFloat(0.25f, 0.75f);

    maxFrequencyClick = randomFloat(0.5f, 1.0f) * 900.0f;
    minFrequencyClick = randomFloat(0.5f, 1.0f) * 40.0f;
    attackTimeFrequencyClick = randomFloat(0.5f, 1.0f) * 10.0f;
    decayTimeFrequencyClick = randomFloat(0.5f, 1.0f) * 40.0f;
    curvednessFrequencyClick = randomFloat(0.1f, 0.2f);

    // Noise
    maxAmplitudeNoise = randomFloat(0.5f, 1.0f) * 0.6f;
    minAmplitudeNoise = 0.0f;
    attackTimeAmplitudeNoise = randomFloat(0.5f, 1.0f) * 10.0f;
    decayTimeAmplitudeNoise = randomFloat(0.5f, 1.0f) * 75.0f;
    curvednessAmplitudeNoise = randomFloat(0.1f, 0.5f);

    noiseFilterFrequency = randomFloat(0.5f, 1.0f) * 3000.0f;

    // FX
    bitCrusher.bits(random(4, 16));
    bitCrusher.sampleRate(random(5512, 44100));

    // Redefine all envelopes
    envelopeSineAmplitude = std::make_unique<Envelope>(maxAmplitudeSine, minAmplitudeSine, attackTimeAmplitudeSine, decayTimeAmplitudeSine, curvednessAmplitudeSine);
    envelopeSineFrequency = std::make_unique<Envelope>(maxFrequencySine, minFrequencySine, attackTimeFrequencySine, decayTimeFrequencySine, curvednessFrequencySine);
    envelopeClickAmplitude = std::make_unique<Envelope>(maxAmplitudeClick, minAmplitudeClick, attackTimeAmplitudeClick, decayTimeAmplitudeClick, curvednessAmplitudeClick);
    envelopeClickFrequency = std::make_unique<Envelope>(maxFrequencyClick, minFrequencyClick, attackTimeFrequencyClick, decayTimeFrequencyClick, curvednessFrequencyClick);
    envelopeNoiseAmplitude = std::make_unique<Envelope>(maxAmplitudeNoise, minAmplitudeNoise, attackTimeAmplitudeNoise, decayTimeAmplitudeNoise, curvednessAmplitudeNoise);

}