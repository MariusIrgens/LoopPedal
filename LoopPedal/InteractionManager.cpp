#include "InteractionManager.h"
#include "SystemController.h"

// Define static members
volatile unsigned long InteractionManager::lastInterruptTime1 = 0;
volatile unsigned long InteractionManager::lastInterruptTime2 = 0;
volatile unsigned long InteractionManager::lastEncoderInterruptTime = 0;
volatile unsigned long InteractionManager::lastFlipInterruptTime = 0;
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
    attachInterrupt(digitalPinToInterrupt(buttonPin1), InteractionManager::button1ISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(buttonPin2), InteractionManager::button2ISR, CHANGE);

    // Potentiometers
    pinMode(potPin1, INPUT);
    pinMode(potPin2, INPUT);

    // LED metronome
    pinMode(LEDRMet_Pin, OUTPUT);
    pinMode(LEDGMet_Pin, OUTPUT);
    pinMode(LEDBMet_Pin, OUTPUT);

    // LED record
    pinMode(LEDRRec_Pin, OUTPUT);
    pinMode(LEDGRec_Pin, OUTPUT);

    // Rotary Encoder
    pinMode(RotEncPinA, INPUT_PULLUP);
    pinMode(RotEncPinB, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(RotEncPinA), InteractionManager::updateEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(RotEncPinB), InteractionManager::updateEncoder, CHANGE);

    // Flip Switch
    pinMode(flipSwitchPin1, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(flipSwitchPin1), InteractionManager::updateFlipSwitch, CHANGE);

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
    analogWrite(LEDRMet_Pin, r);
    analogWrite(LEDGMet_Pin, g);
    analogWrite(LEDBMet_Pin, b);
}

void InteractionManager::lightRecLED(int r, int g)
{
    analogWrite(LEDRRec_Pin, r);
    analogWrite(LEDGRec_Pin, g);
}

void InteractionManager::updateEncoder() {
    // Debounce
    unsigned long currentInterruptTime = millis();
    if (currentInterruptTime - lastEncoderInterruptTime > 50)
    {

        int MSB = digitalRead(instance->RotEncPinA);
        int LSB = digitalRead(instance->RotEncPinB);

        if (MSB == 1 && LSB == 0)
            instance->rotEncTurnDetected("CW");
        else if (MSB == 0 && LSB == 1)
            instance->rotEncTurnDetected("CCW");

        lastEncoderInterruptTime = currentInterruptTime;
    }
}

void InteractionManager::rotEncTurnDetected(String direction) {
    if (direction == "CW" && instance->rotaryActionSetBPM)
        systemController->incrementBPM(2);
    else if (direction == "CCW" && instance->rotaryActionSetBPM)
        systemController->incrementBPM(-2);
}

void InteractionManager::updateFlipSwitch()
{
    unsigned long currentInterruptTime = millis();
    // Debounce
    if (currentInterruptTime - lastFlipInterruptTime > 200) {
        int MSB = digitalRead(instance->flipSwitchPin1);
        Serial.print("Flip: ");
        Serial.println(MSB);
        // change rotary action type
        instance->rotaryActionSetBPM = !instance->rotaryActionSetBPM;
        lastFlipInterruptTime = currentInterruptTime;
    }
}