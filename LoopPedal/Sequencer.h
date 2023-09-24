#ifndef _SEQUENCER_h
#define _SEQUENCER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#pragma once
#include <vector>
#include <memory>
#include <algorithm> 
#include <string>

#include "DrumSound.h"
#include "DrumSoundKick.h"
#include "DrumSoundSnare.h"
#include "DrumSoundTomHigh.h"
#include "DrumSoundTomLow.h"
#include "DrumSoundHihatClosed.h"
#include "DrumSoundHihatOpen.h"
#include "DrumTemplates.h"

enum class DrumType { Kick, Snare, LowTom, HighTom, ClosedHiHat, OpenHiHat, Cymbal };

class AudioManager;

class Sequencer {
public:
    Sequencer(AudioManager* audioManager, AudioMixer4& mixer1, AudioMixer4& mixer2);
    void newSequence();
    void newDrums();
    void nextStep();
    void update(int deltaTime);

    std::unique_ptr<DrumSound> kick;
    std::unique_ptr<DrumSound> snare;
    std::unique_ptr<DrumSound> highTom;
    std::unique_ptr<DrumSound> lowTom;
    std::unique_ptr<DrumSound> closedHiHat;
    std::unique_ptr<DrumSound> openHiHat;
    std::unique_ptr<DrumSound> clap;
    std::unique_ptr<DrumSound> cymbal;

private:
    bool oneMoreHit(int hitNumber, int contribution);
    void pastePatternToSequence(int sequenceStart);
    void addAlwaysHits();
    void addVariableHits();
    void populateVariableHits(std::vector<int>& drumSequence, DrumType drumType);

    std::unique_ptr<DrumTemplates> drumTemplates;
    DrumTemplates::Template templateToUse;
    std::vector<int> kickVariable;
    std::vector<int> snareVariable;
    std::vector<int> closedHiHatVariable;
    std::vector<int> openHiHatVariable;
    float busyness = 0.5;

    int sequenceLength;
    std::vector<std::vector<int>> sequenceSteps;
    std::vector<std::vector<int>> patternSteps;


    bool debugMode = false;
    int currentStep = 0;

    AudioManager* audioManagerRef;
};

#endif

// Example hard-coded sequence:
//sequenceSteps[0] = { 1, 0, 0, 0,  0, 0, 1, 0,  0, 0, 1, 0,  0, 0, 0, 0 };  // kick
//sequenceSteps[1] = { 0, 0, 0, 0,  1, 0, 0, 0,  0, 0, 0, 0,  1, 0, 0, 0 }; // snare
//sequenceSteps[2] = { 0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0 }; // high tom
//sequenceSteps[3] = { 0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0 }; // low tom
//sequenceSteps[4] = { 1, 0, 0, 0,  1, 0, 0, 0,  1, 0, 0, 0,  1, 0, 0, 0 }; // closed hihat
//sequenceSteps[5] = { 0, 0, 1, 0,  0, 0, 0, 0,  0, 0, 1, 0,  0, 0, 0, 0 }; // open hihat