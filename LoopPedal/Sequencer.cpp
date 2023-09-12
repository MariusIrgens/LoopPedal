#include "Sequencer.h"

Sequencer::Sequencer(AudioMixer4& mixer1, AudioMixer4& mixer2)
{
    kick = std::make_unique<DrumSoundKick>(0, mixer1);
    snare = std::make_unique<DrumSoundSnare>(1, mixer1);
    highTom = std::make_unique<DrumSoundTomHigh>(2, mixer1);
    lowTom = std::make_unique<DrumSoundTomLow>(3, mixer1);
    closedHiHat = std::make_unique<DrumSoundHihatClosed>(0, mixer2);
    openHiHat = std::make_unique<DrumSoundHihatOpen>(1, mixer2);

    sequenceSteps.resize(8, std::vector<int>(SEQUENCE_STEPS, 0)); 
    newSequence();
}


void Sequencer::newSequence() {
    // Example hard-coded sequence:
    sequenceSteps[0] = { 1, 0, 0, 0,  0, 0, 1, 0,  0, 0, 1, 0,  0, 0, 0, 0 };  // kick
    sequenceSteps[1] = { 0, 0, 0, 0,  1, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0 }; // snare
    sequenceSteps[2] = { 0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0 }; // high tom
    sequenceSteps[3] = { 0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0 }; // low tom
    sequenceSteps[4] = { 1, 0, 0, 0,  1, 0, 0, 0,  1, 0, 0, 0,  1, 0, 0, 0 }; // closed hihat
    sequenceSteps[5] = { 0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 1, 0,  0, 0, 0, 0 }; // open hihat

}

void Sequencer::newDrums() {
    // run parameter changer function on each drum object (virtual function with override)
}

void Sequencer::nextStep() {

    if (debugMode) {
        Serial.print("Current Step: ");
        Serial.println(currentStep);
    }
    
    if (sequenceSteps[0][currentStep] > 0) kick->trigger(sequenceSteps[0][currentStep]);
    if (sequenceSteps[1][currentStep] > 0) snare->trigger(sequenceSteps[1][currentStep]);
    if (sequenceSteps[2][currentStep] > 0) highTom->trigger(sequenceSteps[1][currentStep]);
    if (sequenceSteps[3][currentStep] > 0) lowTom->trigger(sequenceSteps[1][currentStep]);
    if (sequenceSteps[4][currentStep] > 0) { closedHiHat->trigger(sequenceSteps[1][currentStep]); openHiHat->choke();}
    if (sequenceSteps[5][currentStep] > 0) openHiHat->trigger(sequenceSteps[1][currentStep]);

    currentStep = (currentStep + 1) % SEQUENCE_STEPS;
}

void Sequencer::update(int deltaTime)
{
    kick->update(deltaTime);
    snare->update(deltaTime);
    highTom->update(deltaTime);
    lowTom->update(deltaTime);
    closedHiHat->update(deltaTime);
    openHiHat->update(deltaTime);
}