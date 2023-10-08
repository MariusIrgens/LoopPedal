// Looper.h

#ifndef _LOOPER_h
#define _LOOPER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <Audio.h>
#include <SD.h>
#include <memory>
#include <vector>
#include <string>

#define CS 10


class AudioManager;

class Looper {
public:

    enum class State {
        Idle,
        Recording,
        Looping,
        Overdubbing
    };

    Looper(AudioManager* audioManager, AudioMixer4& mixerAudio, AudioMixer4& mixerLooper);
    void setup();
    void loop();

    void recordButton();
    void eraseButton();
    void startRecording();
    void continueRecording();
    void stopRecording();
    void startPlaying();
    void stopPlaying();
    void startOverdubbing();
    void stopOverdubbing();

    void removeLoop();
    void setMajorBeatCue(bool cue);
    bool getIsRecording();
    bool getIsLooping();

private:

    AudioManager* audioManagerRef;

    File frec;
    std::string primaryFile = "LOOP1.RAW";
    std::string secondaryFile = "LOOP2.RAW";

    State currentState = State::Idle;
    bool recordAction = false;
    bool playAction = false;
    bool eraseAction = false;
    bool majorBeatCue = false;
    bool hasRecording = false;
    int timesLooped = 0;
    int currentMajorBeat = 0;
    int loopMajorBeatStart = 0;
    int loopMajorBeatStop = 9999999;
    int overdubMajorBeatStart = 0;


    // Patching
    AudioRecordQueue recorder;
    AudioPlaySdRaw playRaw1;
    AudioMixer4 inputMixer;

    std::unique_ptr<AudioConnection> patchCordAudMix_InputMix;
    std::unique_ptr<AudioConnection> patchCordLoopPlay_InputMix;

    std::unique_ptr<AudioConnection> patchCordInputMix_LoopRec;
    std::unique_ptr<AudioConnection> patchCordLoopPlay_LoopMix;

};

#endif