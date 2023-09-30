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

#define CS 10


class AudioManager;

class Looper {
public:

    enum class State {
        Idle,
        Recording,
        Looping
    };

    Looper(AudioManager* audioManager, AudioMixer4& mixerAudio, AudioMixer4& mixerLooper);
    void setup();
    void loop();

    void recordButton();
    void stopButton();
    void startRecording();
    void continueRecording();
    void stopRecording();
    void startPlaying();
    void continuePlaying();
    void stopPlaying();

    void removeLoop();
    void setMajorBeatCue(bool cue);
    bool getIsRecording();
    bool getIsLooping();

private:

    File frec;

    State currentState = State::Idle;
    bool pressedRecord = false;
    bool looping = false;
    bool pressedStop = false;
    bool majorBeatCue = false;
    bool hasRecording = false;
    int timesLooped = 0;

    AudioRecordQueue recorder;
    AudioPlaySdRaw playRaw1;

    AudioManager* audioManagerRef;
    std::unique_ptr<AudioConnection> patchCordAudMix_LoopRec;
    std::unique_ptr<AudioConnection> patchCordLoopPlay_LoopMix;
};

#endif