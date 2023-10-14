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
    cymbal = std::make_unique<DrumSoundCymbal>(2, mixer2);

    // Create drum sequence distribution templates
    drumTemplates = std::make_unique<DrumTemplates>();
}

void Sequencer::newSequence(int templateIndex, int tomFillIndex) {

    currentTemplateIndex = templateIndex;
    currentTomFillIndex = tomFillIndex;

    float busyness1and3 = 0.4 + randomFloat(0.0f, 0.2f);
    float busynessXtra2 = 0.3 + randomFloat(0.0f, 0.2f);
    float busynessXtra4 = 0.3 + randomFloat(0.0f, 0.2f);

    // Get template
    templateToUse = drumTemplates->getTemplateByIndex(templateIndex);
    kickVariable = templateToUse.kickVariable;
    snareVariable = templateToUse.snareVariable;
    closedHiHatVariable = templateToUse.closedHihatVariable;
    openHiHatVariable = templateToUse.openHihatVariable;

    // Get tom fill
    tomFillToUse = drumTemplates->getTomFillByIndex(tomFillIndex);

    // Get and set pattern and sequence lengths
    patternLength = templateToUse.patternLength;
    patternSteps.resize(8, std::vector<int>(templateToUse.patternLength, 0));
    sequenceLength = templateToUse.patternLength * 4;
    sequenceSteps.resize(8, std::vector<int>(sequenceLength, 0));

    // Empty pattern and sequence
    for (auto& step : patternSteps) {
        std::fill(step.begin(), step.end(), 0);
    }
    for (auto& step : sequenceSteps) {
        std::fill(step.begin(), step.end(), 0);
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
        patternSteps[0][step - 1] = 100;
    }
    for (int step : templateToUse.snareAlways) {
        patternSteps[1][step - 1] = 100;
    }
    for (int step : templateToUse.closedHihatAlways) {
        patternSteps[4][step - 1] = 100;
    }
    for (int step : templateToUse.openHihatAlways) {
        patternSteps[5][step - 1] = 100;
    }

    // Tom fill
    for (int step : tomFillToUse.highTom) {
        patternSteps[2][(patternLength - 8) + step - 1] = 100;
    }
    for (int step : tomFillToUse.lowTom) {
        patternSteps[3][(patternLength - 8) + step - 1] = 100;
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

void Sequencer::nextStep() {

    if (debugMode) {
        Serial.print("Current Step: ");
        Serial.println(currentStep);
    }
    
    // Main beat
    if (sequenceSteps[0][currentStep] > 0) kick->trigger(sequenceSteps[0][currentStep]);                                    // Kick
    if (sequenceSteps[1][currentStep] > 0) snare->trigger(sequenceSteps[1][currentStep]);                                   // Snare
    if (sequenceSteps[5][currentStep] > 0) openHiHat->trigger(sequenceSteps[1][currentStep]);                               // Open Hihat
    else if (sequenceSteps[4][currentStep] > 0) { closedHiHat->trigger(sequenceSteps[1][currentStep]); openHiHat->choke();} // Closed Hihat - Only play if no Open Hihat. Choke previous Open Hihat.

    // Change
    if (shouldChange)
    {
        if (currentPattern == (patternsBetweenChanges - 1))
        {
            if (sequenceSteps[2][currentStep] > 0) highTom->trigger(sequenceSteps[1][currentStep]);     // High Tom
            if (sequenceSteps[3][currentStep] > 0) lowTom->trigger(sequenceSteps[1][currentStep]);      // Low Tom
        }
        if (currentPattern == 0 && currentStep == 0) cymbal->trigger(100);                              // Cymbal

        // New variation on break
        if (currentPattern == (patternsBetweenChanges - 1) && currentStep == (sequenceLength - 1))
        {
            uint32_t seedForRandomSeed = millis();
            randomSeed(seedForRandomSeed);
            int tomFillIndex = random(0, drumTemplates->getMaxTomFillIndex() + 1); // get random tom fill
            newSequence(currentTemplateIndex, tomFillIndex);  // Use same template and new fill
        }
    }
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
    cymbal->update(deltaTime);
}

int Sequencer::readCurrentStep()
{
    return currentStep;
}

int Sequencer::getPatternLength()
{
    return patternLength;
}

void Sequencer::newDrums() {

    kick->newDrum();
    snare->newDrum();
    closedHiHat->newDrum();
    openHiHat->newDrum();
    cymbal->newDrum();
}

float Sequencer::randomFloat(float min = 0.0f, float max = 1.0f)
{
    // Use 3 decimals
    uint32_t randomInt = random(0, 1000);

    // Convert to a float in [0, 1) range.

    float randFloat = min + (static_cast<float>(randomInt) / 1000.0f) * (max - min);  // Scale and shift
    return randFloat;
}

void Sequencer::incrementCurrentPattern()
{
    currentPattern = (currentPattern + 1) % patternsBetweenChanges;

    if (debugMode)
    {
        Serial.print("Current pattern: ");
        Serial.println(currentPattern);
    }
}

DrumTemplates* Sequencer::getDrumTemplates()
{
    return drumTemplates.get();
}

void Sequencer::setShouldChange(bool newShouldChange)
{
    shouldChange = newShouldChange;
    Serial.print("Change: ");
    Serial.println(shouldChange);
}