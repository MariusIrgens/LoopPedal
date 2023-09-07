#include "DisplayManager.h"
#include "AudioManager.h"

#define FRAMERATE 30

DisplayManager displayManager;
AudioManager audioManager;
int16_t framerate;

void setup() {
    displayManager.setup();
    audioManager.setup();
}

void loop() {
    displayManager.loop();
    delay(FRAMERATE); // Optional delay to reduce screen flickering
}
