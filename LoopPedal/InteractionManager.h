// InteractionManager.h

#ifndef _INTERACTIONMANAGER_h
#define _INTERACTIONMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class SystemController;

class InteractionManager {
public:
    static InteractionManager* instance;  // Static pointer for the singleton instance
    InteractionManager(SystemController* systemContr);
    void setup();
    void onButton1Pressed(); 
    void onButton2Pressed(); 
    int readPotentiometer(int potNumber);
    void blinkLED(int r, int g, int b);
    void lightRecLED(int r, int g);
    void rotEncTurnDetected(String direction);

    static void button1ISR();
    static void button2ISR();
    static void updateEncoder();
    static void updateFlipSwitch();

private:
    SystemController* systemController; // Pointer to creator

    // Inputs used by Audio Shield:
    // 7, 8 (Audio in/out)
    // 10, 11, 12, 13 (SD card)
    // 18, 19 (Audio config)
    // 20, 21, 23 (Audio)

    // Inputs used in design already:
    // 0, 1 (Rotary encoder)
    // 2, 3 (LED record)
    // 3, 4, 6 (LED metronome)
    // 14, 17 (Buttons)
    // 15, 16 (Potentiometers)

    // Buttons
    static const int buttonPin1 = 17;
    static const int buttonPin2 = 14;
    static volatile unsigned long lastInterruptTime1;
    static volatile unsigned long lastInterruptTime2;

    // Pot
    static const int potPin1 = A1;
    static const int potPin2 = A2;
    int pot1Value = 0;
    int pot2Value = 0;

    // LED metronome
    const int LEDRMet_Pin = 4;
    const int LEDGMet_Pin = 2;
    const int LEDBMet_Pin = 3;

    // LED Record
    const int LEDRRec_Pin = 5;
    const int LEDGRec_Pin = 6;

    // Rotary Encoder
    const int RotEncPinA = 0;
    const int RotEncPinB = 1;
    int lastEncoded = 0;
    int lastMSB = 0;
    int lastLSB = 0;
    static volatile unsigned long lastEncoderInterruptTime;
    bool rotaryActionSetBPM = true;

    // Flip switch
    static const int flipSwitchPin1 = A8;
    static volatile unsigned long lastFlipInterruptTime;
};

#endif
