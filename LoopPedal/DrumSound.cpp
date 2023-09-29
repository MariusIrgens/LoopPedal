#include "DrumSound.h"

DrumSound::DrumSound(int mixerChannel, AudioMixer4& mixer)
{

}

void DrumSound::trigger(int velocity) {

}

void DrumSound::update(int resolution)
{

}

void DrumSound::choke()
{

}

void DrumSound::newDrum()
{

}

float DrumSound::randomFloat(float min = 0.0f, float max = 1.0f)
{
    // Use 3 decimals
    uint32_t randomInt = random(0, 1000);

    // Convert to a float in [0, 1) range.

    float randFloat = min + (static_cast<float>(randomInt) / 1000.0f) * (max - min);  // Scale and shift
    return randFloat;
}