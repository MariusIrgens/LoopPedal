#include "InteractionManager.h"
#include "SystemController.h"

// Define static members
volatile unsigned long InteractionManager::lastInterruptTime1 = 0;
volatile unsigned long InteractionManager::lastInterruptTime2 = 0;
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
    attachInterrupt(digitalPinToInterrupt(buttonPin1), InteractionManager::button1ISR, FALLING);
    attachInterrupt(digitalPinToInterrupt(buttonPin2), InteractionManager::button2ISR, FALLING);

    // Potentiometers
    pinMode(potPin1, INPUT);
    pinMode(potPin2, INPUT);

    // LED
    pinMode(LEDR_Pin, OUTPUT);
    pinMode(LEDG_Pin, OUTPUT);
    pinMode(LEDB_Pin, OUTPUT);

    // TEST
    //pinMode(test_Pin, OUTPUT);
    //analogWrite(test_Pin, 255);


}

void InteractionManager::button1ISR() {
    unsigned long currentInterruptTime = millis();
    // Debounce
    if (currentInterruptTime - lastInterruptTime1 > 200) {
        instance->onButton1Pressed();
        lastInterruptTime1 = currentInterruptTime;
    }
}

void InteractionManager::button2ISR() {
    unsigned long currentInterruptTime = millis();
    // Debounce
    if (currentInterruptTime - lastInterruptTime2 > 200) {
        instance->onButton2Pressed();
        lastInterruptTime2 = currentInterruptTime;
    }
}

void InteractionManager::onButton1Pressed() {
    systemController->newSequence();
}

void InteractionManager::onButton2Pressed() {
    systemController->record();
}

int InteractionManager::readPotentiometer(int potNumber) {
    switch (potNumber)
    {
    case 1:
        return analogRead(potPin1);
        break;
    case 2:
        return analogRead(potPin2);
        break;
    default:
        return 0;
        break;
    }
}

void InteractionManager::blinkLED(int r, int g, int b) {
    analogWrite(LEDR_Pin, r);
    analogWrite(LEDG_Pin, g);
    analogWrite(LEDB_Pin, b);
}
