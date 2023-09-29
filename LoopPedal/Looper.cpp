#include "Looper.h"
#include "AudioManager.h"

Looper::Looper(AudioManager* audioManager, AudioMixer4& mixerAudio, AudioMixer4& mixerLooper)
    : audioManagerRef(audioManager)
{
    // FROM audio-mixer TO loop-recorder
    patchCordAudMix_LoopRec = std::make_unique<AudioConnection>(mixerAudio, 0, recorder, 0);

    // FROM loop-player TO loop-mixer (wet)
    patchCordLoopPlay_LoopMix = std::make_unique<AudioConnection>(playRaw1, 0, mixerLooper, 1);

}

void Looper::setup()
{
    pinMode(CS, OUTPUT);

    // Initialize the SD card
    SPI.setMOSI(11);
    SPI.setMISO(12);
    SPI.setSCK(13);
    if (!(SD.begin(CS)))
    {
        Serial.println("Unable to access the SD card");
    }
    else
    {
        Serial.println("SD card accessed!");
    }
}

void Looper::loop()
{
    // Respond to button presses
    if (pressedRecord)
    {
        Serial.println("Record Button Press");
        if (currentState == State::Playing) stopPlaying();
        if (currentState == State::Idle) startRecording();
        pressedRecord = false;
    }
    if (pressedPlay)
    {
        Serial.println("Play Button Press");
        if (currentState == State::Recording) stopRecording();
        if (currentState == State::Idle) startPlaying();
        pressedPlay = false;
    }
    if (pressedStop) 
    {
        Serial.println("Stop Button Press");
        if (currentState == State::Recording) stopRecording();
        if (currentState == State::Playing) stopPlaying();
        removeLoop();
        pressedStop = false;
    }

    // If we're playing or recording, carry on...
    if (currentState == State::Recording) {
        continueRecording();
    }
    if (currentState == State::Playing) {
        continuePlaying();
    }
}

void Looper::recordButton()
{
    switch (currentState)
    {
    case State::Idle:
        pressedRecord = true;
        break;
    case State::Recording:
        pressedPlay = true;
        break;
    case State::Playing:
        pressedRecord = true;
        break;
    default:
        break;
    }
}

void Looper::stopButton()
{
    pressedStop = true;
}

void Looper::removeLoop()
{
    frec.close();
    if (SD.exists("RECORD.RAW")) 
    {
        SD.remove("RECORD.RAW");
        if (SD.exists("RECORD.RAW"))
            Serial.println("Error: Unable to delete the old recording file.");
        else
            Serial.println("Removed old file.");
    }
    recorder.clear();
}

void Looper::startRecording() {

    removeLoop();
    Serial.println("start Recording..."); 
    frec = SD.open("RECORD.RAW", FILE_WRITE);
    if (frec) {
        recorder.begin();
        currentState = State::Recording;
    }
}

void Looper::continueRecording() 
{
    if (recorder.available() >= 2) {
        byte buffer[512];
        // Fetch 2 blocks from the audio library and copy
        // into a 512 byte buffer.  The Arduino SD library
        // is most efficient when full 512 byte sector size
        // writes are used.
        memcpy(buffer, recorder.readBuffer(), 256);
        recorder.freeBuffer();
        memcpy(buffer + 256, recorder.readBuffer(), 256);
        recorder.freeBuffer();
        // write all 512 bytes to the SD card
        //elapsedMicros usec = 0;
        frec.write(buffer, 512);
        // Uncomment these lines to see how long SD writes
        // are taking.  A pair of audio blocks arrives every
        // 5802 microseconds, so hopefully most of the writes
        // take well under 5802 us.  Some will take more, as
        // the SD library also must write to the FAT tables
        // and the SD card controller manages media erase and
        // wear leveling.  The queue1 object can buffer
        // approximately 301700 us of audio, to allow time
        // for occasional high SD card latency, as long as
        // the average write time is under 5802 us.
        //Serial.print("SD write, us=");
        //Serial.println(usec);
    }
}

void Looper::stopRecording() {
    Serial.println("stop Recording");
    recorder.end();
    if (currentState == State::Recording) {
        while (recorder.available() > 0) {
            byte buffer[256];
            memcpy(buffer, recorder.readBuffer(), 256);
            recorder.freeBuffer();
            frec.write(buffer, 256);
        }
        frec.close();
    }
    recorder.clear();
    currentState = State::Idle;
}

void Looper::startPlaying() {
    Serial.println("start Playing");
    playRaw1.play("RECORD.RAW");
    currentState = State::Playing;
}

void Looper::continuePlaying() {
    if (!playRaw1.isPlaying()) {
        stopPlaying();
    }
}

void Looper::stopPlaying() {
    Serial.println("stop Playing");
    playRaw1.stop();
    currentState = State::Idle;
}
