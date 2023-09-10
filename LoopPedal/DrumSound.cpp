#include "DrumSound.h"

DrumSound::DrumSound(int mixerChannel, AudioMixer4& mixer)
    : patchCord(drumSynth, 0, mixer, mixerChannel) 
{

}

void DrumSound::trigger() {
    // set parameters for each trigger, based on incomming velocity (make it an argument for this function)
    drumSynth.frequency(200.0);
    drumSynth.length(500);
    drumSynth.noteOn();

    if (debugMode) {
        Serial.print("Drumsound");
        
        //Serial.print("\ncpu_cycles");
        //Serial.print(drumSynth.cpu_cycles);
        //Serial.print("\ncpu_cycles_max");
        //Serial.print(drumSynth.cpu_cycles_max);
        //Serial.print("\ncpu_cycles_total");
        //Serial.print(drumSynth.cpu_cycles_total);
        //Serial.print("\ncpu_cycles_total_max");
        //Serial.print(drumSynth.cpu_cycles_total_max);
        //Serial.print("\nmemory_used");
        //Serial.print(drumSynth.memory_used);
        //Serial.print("\nmemory_used_max");
        //Serial.print(drumSynth.memory_used_max);   
    }
}
