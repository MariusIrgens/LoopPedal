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
#include "DrumSound.h"
#include "DrumSoundKick.h"
#include "DrumSoundSnare.h"

class Sequencer {
public:
    Sequencer(AudioMixer4& mixer1, AudioMixer4& mixer2);
    void newSequence();
    void newDrums();
    void nextStep();
    void update(int deltaTime);

    std::unique_ptr<DrumSound> kick;
    std::unique_ptr<DrumSound> snare;
    std::unique_ptr<DrumSound> clap;
    std::unique_ptr<DrumSound> openHiHat;
    std::unique_ptr<DrumSound> closedHiHat;
    std::unique_ptr<DrumSound> highTom;
    std::unique_ptr<DrumSound> lowTom;
    std::unique_ptr<DrumSound> cymbal;

private:
    static const int SEQUENCE_STEPS = 16; // Number of steps in a sequence
    std::vector<std::vector<int>> sequenceSteps;  // 2D vector for sequences
    bool debugMode = false;
    int currentStep = 0;
};

#endif

