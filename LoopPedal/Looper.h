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

#define SPI_SPEED SD_SCK_MHZ(4)
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

    // Start or stop recording
    void record();

    // Main loop handling recording and playback
    void update();

    // Reset the loop
    void reset();

private:

    File frec;

    State currentState = State::Idle;

    std::vector<int16_t> recordedBuffer; // The buffer to store recorded audio
    size_t playbackBufferIndex = 0; // Index to keep track of playback position

    bool isRecording = false;
    bool hasLoop = false;
    uint32_t loopLength = 0;
    uint32_t loopStartTime = 0;

    AudioRecordQueue recorder;
    AudioPlayQueue player;
    AudioManager* audioManagerRef;

    std::unique_ptr<AudioConnection> patchCordAudMix_LoopRec;
    std::unique_ptr<AudioConnection> patchCordLoopPlay_LoopMix;
};

#endif