#include "Sequencer.h"

Sequencer::Sequencer(AudioMixer4& mixer1, AudioMixer4& mixer2)
{
    kick = std::make_unique<DrumSoundKick>(0, mixer1);
    snare = std::make_unique<DrumSoundSnare>(1, mixer1);

    sequenceSteps.resize(8, std::vector<int>(SEQUENCE_STEPS, 0)); 
    newSequence();
}


void Sequencer::newSequence() {
    // Example hard-coded sequence:
    sequenceSteps[0] = { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 };  // kick
    sequenceSteps[1] = { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 }; // nsnare
}

void Sequencer::newDrums() {
    // change parameters
}

void Sequencer::nextStep() {

    if (debugMode) {
        Serial.print("Current Step: ");
        Serial.println(currentStep);
    }

    if (sequenceSteps[0][currentStep] == 1) kick->trigger(1);
    if (sequenceSteps[1][currentStep] == 1) snare->trigger(1);
    // ... Continue for other drums

    currentStep = (currentStep + 1) % SEQUENCE_STEPS;
}

void Sequencer::update(int deltaTime)
{
    kick->update(deltaTime);
}