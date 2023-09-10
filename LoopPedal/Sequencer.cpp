#include "Sequencer.h"

Sequencer::Sequencer(AudioMixer4& mixer1, AudioMixer4& mixer2)
    : kick(0, mixer1), snare(1, mixer1), clap(2, mixer1), openHiHat(3, mixer1),
    closedHiHat(0, mixer2), highTom(1, mixer2), lowTom(2, mixer2), cymbal(3, mixer2)
{
    sequenceSteps.resize(8, std::vector<int>(8, 0));
    newSequence();
}


void Sequencer::newSequence() {
    // Example hard-coded sequence:
    sequenceSteps[0] = { 1, 0, 0, 1, 0, 0, 0, 0 };  // kick
    sequenceSteps[1] = { 0, 0, 1, 0, 0, 0, 1, 0 };  // snare
    // ... and so on for other drum sounds.
}

void Sequencer::newDrums() {
    // Example parameter updates:
    // kick.setParameter(...);
    // snare.setParameter(...);
    // ... and so on for each drum sound.
}

void Sequencer::nextStep() {

    if (debugMode) {
        Serial.print("Current Step: ");
        Serial.println(currentStep);
    }

    if (sequenceSteps[0][currentStep] == 1) kick.trigger();
    if (sequenceSteps[1][currentStep] == 1) snare.trigger();
    // ... Continue for other drums

    currentStep = (currentStep + 1) % sequenceSteps[0].size(); // Move to the next step and loop back if needed
}

