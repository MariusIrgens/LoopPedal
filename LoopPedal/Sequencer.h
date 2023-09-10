// Sequencer.h

#ifndef _SEQUENCER_h
#define _SEQUENCER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#pragma once

#include <vector>
#include "DrumSound.h"

class Sequencer {
public:
    Sequencer(AudioMixer4& mixer1, AudioMixer4& mixer2);
    void newSequence();
    void newDrums();
    void nextStep();

private:
    DrumSound kick, snare, clap, openHiHat, closedHiHat, highTom, lowTom, cymbal;
    std::vector<std::vector<int>> sequenceSteps;  // 2D vector for sequences
    bool debugMode = false;
    int currentStep = 0;
};

#endif

