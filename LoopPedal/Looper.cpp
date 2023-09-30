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
    if (pressedRecord && majorBeatCue)
    {
        Serial.println("Record Button Press");
        if (currentState == State::Looping) stopPlaying();
        if (currentState == State::Idle) startRecording();
        pressedRecord = false;
        majorBeatCue = false;
    }
    if (looping && majorBeatCue)
    {
        //Serial.println("Play Button Press");
        if (currentState == State::Recording) stopRecording();
        if (currentState == State::Idle) startPlaying();
        //pressedPlay = false;
    }
    if (pressedStop) 
    {
        looping = false;

        Serial.println("Stop Button Press");
        if (currentState == State::Recording) stopRecording();
        if (currentState == State::Looping) stopPlaying();
        removeLoop();
        pressedStop = false;
    }

    // If we're playing or recording, carry on...
    if (currentState == State::Recording) {
        
        continueRecording();
    }
    if (currentState == State::Looping) {
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
        looping = true;
        break;
    case State::Looping:
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

void Looper::startRecording() 
{

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

void Looper::stopRecording() 
{
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

void Looper::startPlaying() 
{
    timesLooped++;
    std::string message = "Play loop " + std::to_string(timesLooped);
    Serial.println(message.c_str());
    playRaw1.play("RECORD.RAW");
    currentState = State::Looping;
}

void Looper::continuePlaying() 
{
    if (!playRaw1.isPlaying()) {
        stopPlaying();
    }
}

void Looper::stopPlaying() 
{
    std::string message = "Stop loop " + std::to_string(timesLooped);
    Serial.println(message.c_str());
    playRaw1.stop();
    currentState = State::Idle;
}

void Looper::setMajorBeatCue(bool cue)
{
    majorBeatCue = cue;
}

bool Looper::getIsRecording() 
{
    return currentState == State::Recording;
}

bool Looper::getIsLooping()
{
    return currentState == State::Looping;
}

