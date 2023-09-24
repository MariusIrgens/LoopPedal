#include "DisplayManager.h"
#include "AudioManager.h"

#define FRAMERATE 30

DisplayManager displayManager;
AudioManager audioManager;

void setup() {
    Serial.begin(9600);

    displayManager.setup();
    audioManager.setup();
}

void loop() {
    displayManager.loop();
    audioManager.loop();
    //delay(FRAMERATE); // Optional delay to reduce screen flickering
}
