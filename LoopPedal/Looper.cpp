#include "Looper.h"
#include "AudioManager.h"

Looper::Looper(AudioManager* audioManager, AudioMixer4& mixerAudio, AudioMixer4& mixerLooper)
    : audioManagerRef(audioManager)
{
    // FROM audio-mixer TO loop-recorder
    patchCordAudMix_LoopRec = std::make_unique<AudioConnection>(mixerAudio, 0, recorder, 0);

    // FROM loop-player TO loop-mixer (wet)
    patchCordLoopPlay_LoopMix = std::make_unique<AudioConnection>(player, 0, mixerLooper, 1);

}

void Looper::setup()
{
    pinMode(CS, OUTPUT);

    // Initialize the SD card
    SPI.setMOSI(11);
    SPI.setMISO(12);
    SPI.setSCK(13);
    //SD.begin(CS);

    if (!(SD.begin(CS))) 
    {
        Serial.println("Unable to access the SD card");
    }
}

void Looper::record() {
    switch (currentState) {
    case State::Idle:
        Serial.println("Recording started!");
        recorder.begin();
        currentState = State::Recording;
        loopStartTime = millis();
        break;

    case State::Recording:
        Serial.println("Recording ended!");
        recorder.end();
        loopLength = recordedBuffer.size() / AUDIO_BLOCK_SAMPLES;
        currentState = State::Idle;
        hasLoop = true;
        playbackBufferIndex = 0; // Reset playback index
        break;


    case State::Playing:
        // Handle if needed, or do nothing.
        break;
    }
}

void Looper::update() {

    //if (currentState == State::Recording) {
    //    while (recorder.available()) {
    //        int16_t* buffer = recorder.readBuffer();
    //        if (buffer != NULL) {
    //            // Determine the number of bytes to copy (2 bytes per int16_t)
    //            size_t bytesToCopy = AUDIO_BLOCK_SAMPLES * sizeof(int16_t);

    //            // Resize the recordedBuffer to accommodate the new data
    //            size_t currentSize = recordedBuffer.size();
    //            recordedBuffer.resize(currentSize + AUDIO_BLOCK_SAMPLES);

    //            // Use memcpy to copy the data
    //            memcpy(&recordedBuffer[currentSize], buffer, bytesToCopy);
    //            recorder.freeBuffer();
    //        }
    //    }
    //}
    //else if (currentState == State::Idle && hasLoop) {
    //    if (playbackBufferIndex < recordedBuffer.size()) {
    //        player.play(&recordedBuffer[playbackBufferIndex], AUDIO_BLOCK_SAMPLES);
    //        playbackBufferIndex += AUDIO_BLOCK_SAMPLES;
    //    }
    //    else {
    //        playbackBufferIndex = 0; // Loop the playback
    //    }
    //}
}

void Looper::reset() {
    recordedBuffer.clear();
    recorder.clear();
    currentState = State::Idle;
    hasLoop = false;
}