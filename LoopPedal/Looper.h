// Looper.h

#ifndef _LOOPER_h
#define _LOOPER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <Audio.h>
#include <memory>
#include <vector>

//#define AUDIO_BLOCK_SAMPLES 128
// Use these with the Teensy Audio Shield

#define CS 10


class AudioManager;

class Looper {
public:

    enum class State {
        Idle,
        Recording,
        Playing
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

private:

    File frec;

    State currentState = State::Idle;
    bool pressedRecord = false;
    bool pressedPlay = false;
    bool pressedStop = false;

    AudioRecordQueue recorder;
    AudioPlaySdRaw playRaw1;

    AudioManager* audioManagerRef;
    std::unique_ptr<AudioConnection> patchCordAudMix_LoopRec;
    std::unique_ptr<AudioConnection> patchCordLoopPlay_LoopMix;
};

#endif