#include "InteractionManager.h"
#include "SystemController.h"

// Define static members
volatile unsigned long InteractionManager::lastInterruptTime1 = 0;
volatile unsigned long InteractionManager::lastInterruptTime2 = 0;
volatile unsigned long InteractionManager::lastInterruptTime3 = 0;
InteractionManager* InteractionManager::instance = nullptr; 

InteractionManager::InteractionManager(SystemController* systemContr) 
    : systemController(systemContr)
{
    instance = this;
}

void InteractionManager::setup() {

    // Buttons
    pinMode(buttonPin1, INPUT_PULLUP);
    pinMode(buttonPin2, INPUT_PULLUP);
    pinMode(buttonPin3, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(buttonPin1), InteractionManager::button1ISR, FALLING);
    attachInterrupt(digitalPinToInterrupt(buttonPin2), InteractionManager::button2ISR, FALLING);
    attachInterrupt(digitalPinToInterrupt(buttonPin3), InteractionManager::button3ISR, FALLING);

    // Potentiometer
    pinMode(potPin, INPUT);
    // LED
    pinMode(LEDR_Pin, OUTPUT);
    pinMode(LEDG_Pin, OUTPUT);
    pinMode(LEDB_Pin, OUTPUT);

}

void InteractionManager::loop() {

}

void InteractionManager::button1ISR() {
    unsigned long currentInterruptTime = millis();
    // Debounce
    if (currentInterruptTime - lastInterruptTime1 > 50) {
        instance->onButton1Pressed();
        lastInterruptTime1 = currentInterruptTime;
    }
}

void InteractionManager::button2ISR() {
    unsigned long currentInterruptTime = millis();
    // Debounce
    if (currentInterruptTime - lastInterruptTime2 > 50) {
        instance->onButton2Pressed();
        lastInterruptTime2 = currentInterruptTime;
    }
}

void InteractionManager::button3ISR() {
    unsigned long currentInterruptTime = millis();
    // Debounce
    if (currentInterruptTime - lastInterruptTime3 > 50) {
        instance->onButton3Pressed();
        lastInterruptTime3 = currentInterruptTime;
    }
}

void InteractionManager::onButton1Pressed() {
    systemController->newSequence();
}

void InteractionManager::onButton2Pressed() {
    systemController->newDrums();
}

void InteractionManager::onButton3Pressed() {
    //systemController->recordLoop();
    systemController->recordLoop();
}

int InteractionManager::readPotentiometer() {
    return analogRead(potPin);
}

void InteractionManager::blinkLED(int r, int g, int b) {
    analogWrite(LEDR_Pin, r);
    analogWrite(LEDG_Pin, g);
    analogWrite(LEDB_Pin, b);
}
