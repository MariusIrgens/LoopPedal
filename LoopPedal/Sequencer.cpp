#include "Sequencer.h"
#include "AudioManager.h"

Sequencer::Sequencer(AudioManager* audioManager, AudioMixer4& mixer1, AudioMixer4& mixer2) 
    : audioManagerRef(audioManager)
{
    // Create sound objects
    kick = std::make_unique<DrumSoundKick>(0, mixer1);
    snare = std::make_unique<DrumSoundSnare>(1, mixer1);
    highTom = std::make_unique<DrumSoundTomHigh>(2, mixer1);
    lowTom = std::make_unique<DrumSoundTomLow>(3, mixer1);
    closedHiHat = std::make_unique<DrumSoundHihatClosed>(0, mixer2);
    openHiHat = std::make_unique<DrumSoundHihatOpen>(1, mixer2);

    // Create drum sequence distribution templates
    drumTemplates = std::make_unique<DrumTemplates>();

    // create random beat using a distribution
    newSequence();
}

void Sequencer::newSequence() {

    // Seed the random number generator
    randomSeed(0);
    float busyness1and3 = 0.5;
    float busynessXtra2 = 0.3;
    float busynessXtra4 = 0.4;
    int templateIndex = 0;

    // Set speed (for random speed at sequence change - call from touch instead)
    //int newSixteenthNote = 125000;
    //audioManagerRef->setDrumTimerInterval(newSixteenthNote);

    // Get template
    templateToUse = drumTemplates->getTemplateByIndex(templateIndex);
    kickVariable = templateToUse.kickVariable;
    snareVariable = templateToUse.snareVariable;
    closedHiHatVariable = templateToUse.closedHihatVariable;
    openHiHatVariable = templateToUse.openHihatVariable;

    // Get pattern length and set sequence length
    patternSteps.resize(8, std::vector<int>(templateToUse.patternLength, 0));
    sequenceLength = templateToUse.patternLength * 4;
    sequenceSteps.resize(8, std::vector<int>(sequenceLength, 0));

    // Reset sequence
    for (auto& seq : sequenceSteps) {
        std::fill(seq.begin(), seq.end(), 0);
    }

    // CREATE SEQUENCE
    
    // Pattern 1 and 3 is normal
    busyness = busyness1and3;
    addAlwaysHits();
    addVariableHits();
    pastePatternToSequence(0);
    pastePatternToSequence(templateToUse.patternLength * 2);
    // Pattern 2 adds hits
    busyness = busynessXtra2;
    addVariableHits();
    pastePatternToSequence(templateToUse.patternLength);
    // Pattern 4 adds even more hits
    busyness = busynessXtra4;
    addVariableHits();
    pastePatternToSequence(templateToUse.patternLength * 3);
}

void Sequencer::pastePatternToSequence(int sequenceStart)
{
    for (size_t i = 0; i < sequenceSteps.size(); ++i) // for each drum sound
    {
        for (int j = 0; j < templateToUse.patternLength; ++j) // for each step
        {
            sequenceSteps[i][sequenceStart + j] = patternSteps[i][j];
        }
    }
}

void Sequencer::addAlwaysHits()
{
    // Set always hits (adjusting for 0-based index)
    for (int step : templateToUse.kickAlways) {
        patternSteps[0][step - 1] = 1;
    }
    for (int step : templateToUse.snareAlways) {
        patternSteps[1][step - 1] = 1;
    }
    for (int step : templateToUse.closedHihatAlways) {
        patternSteps[4][step - 1] = 1;
    }
    for (int step : templateToUse.openHihatAlways) {
        patternSteps[5][step - 1] = 1;
    } 
}

void Sequencer::addVariableHits()
{
    // Set variable hits
    populateVariableHits(patternSteps[0], DrumType::Kick);
    populateVariableHits(patternSteps[1], DrumType::Snare);
    populateVariableHits(patternSteps[4], DrumType::ClosedHiHat);
    populateVariableHits(patternSteps[5], DrumType::OpenHiHat);
}

void Sequencer::populateVariableHits(std::vector<int>& drumPattern, DrumType drumType)
{
    int hitNumber = 1;
    int hitVelocity = 1;
    std::string drumString;
    std::vector<int>* distribution = nullptr;

    // Select distribution based on drumType
    switch (drumType)
    {
    case DrumType::Kick:
        distribution = &kickVariable;
        drumString = "kick";
        break;
    case DrumType::Snare:
        distribution = &snareVariable;
        drumString = "snare";
        break;
    case DrumType::ClosedHiHat:
        distribution = &closedHiHatVariable;
        drumString = "closed hihat";
        break;
    case DrumType::OpenHiHat:
        distribution = &openHiHatVariable;
        drumString = "open hihat";
        break;
    default:
        return;  // Exit the function early if an unknown drum type is given.
    }

    // calculate the contributing factor - higher if there are more hits in the distribution
    int contribution = (int)( ((float)distribution->size() / (float)templateToUse.maxArraySize) * 100.0f );

    //if (debugMode) {
    //    std::string message = "contribution " + drumString + ": " + std::to_string(contribution);
    //    Serial.println(message.c_str());
    //}

    while (!distribution->empty() && oneMoreHit(hitNumber, contribution))
    {
        int randomValue = random(distribution->size());
        int hitPlacement = (*distribution)[randomValue];
        drumPattern[hitPlacement] = hitVelocity;

        //if (debugMode) {
        //    std::string message = "Added random hit to " + drumString + " at " + std::to_string(hitPlacement);
        //    Serial.println(message.c_str());
        //}

        // Remove all instances of the used element from the distribution copy
        distribution->erase(std::remove(distribution->begin(), distribution->end(), hitPlacement), distribution->end());
        hitNumber++;
    }
}

bool Sequencer::oneMoreHit(int hitNumber, int contribution)
{
    int chance = 100 + contribution;
    for (int i = 1; i <= hitNumber; i++)
    {
        chance *= busyness;
    }

    int randomValue = random(0, 100);
    if (randomValue < chance)
        return true;
    else
        return false;
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

    currentStep = (currentStep + 1) % sequenceLength;
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