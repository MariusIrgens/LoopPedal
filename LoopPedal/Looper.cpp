#include "Looper.h"
#include "AudioManager.h"
#include "SystemController.h"


Looper::Looper(AudioManager* audioManager, AudioMixer4& mixerAudio, AudioMixer4& mixerLooper)
    : audioManagerRef(audioManager)
{
    // FROM audio-mixer TO input-mixer
    patchCordAudMix_InputMix = std::make_unique<AudioConnection>(mixerAudio, 0, inputMixer, 0);

    // FROM input-mixer TO loop-recorder
    patchCordInputMix_LoopRec = std::make_unique<AudioConnection>(inputMixer, 0, recorder, 0);

    // FROM loop-player TO input-mixer (Reinput)
    patchCordLoopPlay_InputMix = std::make_unique<AudioConnection>(playRaw1, 0, inputMixer, 1);

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
        removeLoop();
    }

    inputMixer.gain(0, 1.0f);
    inputMixer.gain(1, 1.0f);

}

void Looper::loop()
{
    if (majorBeatCue)
    {
        currentMajorBeat++;
        majorBeatCue = false;

        // Respond to button presses
        if (recordAction)
        {
            switch (currentState)
            {
            // Start Recording
            case State::Idle:
                startRecording();
                currentState = State::Recording;
                break;
            // Start Overdubbing
            //case State::Looping:
            //    startOverdubbing();             
            //    currentState = State::Overdubbing;        // Need to fix SD-can-not-read-and-write-at-same-time problem first!
            //    break;
            default:
                break;
            }
            recordAction = false;
        }

        else if (playAction)
        {
            switch (currentState)
            {
            case State::Recording:
                stopRecording();
                currentState = State::Looping;
                break;
            case State::Overdubbing:
                stopOverdubbing();
                currentState = State::Looping;
                break;
            default:
                break;
            }
            playAction = false;
        }

        // Restart recorded sample on correct place
        if (currentState == State::Looping && (currentMajorBeat - loopMajorBeatStart) % (loopMajorBeatStop - loopMajorBeatStart) == 0)
        {
            startPlaying();
        }
       
    }

    if (eraseAction)
    {
        Serial.println("Erase");
        switch (currentState)
        {
        case State::Looping:
            stopPlaying();
            removeLoop();
            currentState = State::Idle;
            break;
        case State::Recording:
            stopRecording();
            removeLoop();
            currentState = State::Idle;
            break;
        case State::Overdubbing:
            stopOverdubbing(); 
            removeLoop(); // Start from scratch (or else I have to store all intermediate recordings)
            currentState = State::Idle; 
            break;
        default:
            break;
        }
        eraseAction = false;
    }

    if (currentState == State::Recording) {
        continueRecording();
    }

    if (currentState == State::Overdubbing) {
        continueRecording();
    }

    // LED
    switch (currentState)
    {
    case State::Idle:
        audioManagerRef->getSystemController()->lightRecLED(0);
        break;
    case State::Looping:
        audioManagerRef->getSystemController()->lightRecLED(1);
        break;
    case State::Recording:
        audioManagerRef->getSystemController()->lightRecLED(2);
        break;
    case State::Overdubbing:
        
        break;
    default:
        break;
    }
}

void Looper::recordButton()
{
    switch (currentState)
    {
    case State::Idle:
        recordAction = true; // perform record action
        break;
    case State::Looping:
        recordAction = true; // perform record action
        break;
    case State::Recording:
        playAction = true; // perform play action
        break;
    case State::Overdubbing:
        playAction = true; // perform play action
        break;
    default:
        break;
    }
}

void Looper::eraseButton()
{
    eraseAction = true; // perform erase action
}

void Looper::removeLoop()
{
    if (frec) {
        frec.close();
    }
    if (SD.exists(primaryFile.c_str()))
    {
        SD.remove(primaryFile.c_str());
        Serial.println("Removed primary file: ");
        Serial.println(primaryFile.c_str());
    }
    if (SD.exists(secondaryFile.c_str()))
    {
        SD.remove(secondaryFile.c_str());
        Serial.println("Removed secondary file: ");
        Serial.println(secondaryFile.c_str());
    }
    recorder.clear();
}

void Looper::startRecording()
{
    removeLoop();

    timesLooped = 0;
    loopMajorBeatStart = currentMajorBeat;              // set loop counter start pos
    Serial.println("start Recording");               
    frec = SD.open(primaryFile.c_str(), FILE_WRITE);    // open new file for writing
    if (frec) {
        recorder.begin();                               // start new recording 
    }
    else {
        Serial.println("Could not start frec (startRecording)!"); // add error handling
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
    loopMajorBeatStop = currentMajorBeat;              // set loop counter stop pos
    std::string message = "Stop recording. Start: " + std::to_string(loopMajorBeatStart) + ", Stop: " + std::to_string(loopMajorBeatStop);
    Serial.println(message.c_str());

    recorder.end();                                     // end current recording
    while (recorder.available() > 0) {                  // push remaining buffer to file
        byte buffer[256];
        memcpy(buffer, recorder.readBuffer(), 256);
        recorder.freeBuffer();
        frec.write(buffer, 256);
    }
    frec.close();                                       // close file
    recorder.clear();                                   // clear file
}

void Looper::startPlaying()
{
    stopPlaying();

    timesLooped++;
    //std::string message = "Play loop " + std::to_string(timesLooped);
    //Serial.println(message.c_str());

    playRaw1.play(primaryFile.c_str()); // Play the primaryFile
}

void Looper::stopPlaying() 
{
    // If playing, stop playing

    if (playRaw1.isPlaying())
        playRaw1.stop();
}

void Looper::startOverdubbing()
{
    overdubMajorBeatStart = currentMajorBeat;
    if (SD.exists(secondaryFile.c_str()))
    {
        SD.remove(secondaryFile.c_str());
        Serial.println("Removed secondary file: ");
        Serial.println(secondaryFile.c_str());
    }

    Serial.println("Start Overdubbing...");
    frec = SD.open(secondaryFile.c_str(), FILE_WRITE); // Record into secondaryFile
    if (frec) {
        recorder.begin();
    }
    else {
        Serial.println("Could not start frec (startOverdubbing)!"); // add error handling
    }
}

void Looper::stopOverdubbing()
{
    loopMajorBeatStart = overdubMajorBeatStart;
    loopMajorBeatStop = currentMajorBeat;
    std::string message = "Stop overdubbing. Start: " + std::to_string(loopMajorBeatStart) + ", Stop: " + std::to_string(loopMajorBeatStop);
    Serial.println(message.c_str());

    Serial.println("Stop Overdubbing");
    recorder.end();
    while (recorder.available() > 0) {
        byte buffer[256];
        memcpy(buffer, recorder.readBuffer(), 256);
        recorder.freeBuffer();
        frec.write(buffer, 256);
        frec.close();
    }
    recorder.clear();

    // After stopping overdubbing, swap the file roles
    std::string temp = primaryFile;
    primaryFile = secondaryFile;
    secondaryFile = temp;
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

