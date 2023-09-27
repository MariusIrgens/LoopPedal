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

    static void button1ISR(); // ISR for button 1
    static void button2ISR(); // ISR for button 2

private:
    SystemController* systemController; // Pointer to creator

    // Buttons
    static const int buttonPin1 = 14;
    static const int buttonPin2 = 17;
    static volatile unsigned long lastInterruptTime1;
    static volatile unsigned long lastInterruptTime2;

    // Pot
    static const int potPin1 = A1;
    static const int potPin2 = A2;
    int pot1Value = 0;
    int pot2Value = 0;

    // LED
    const int LEDR_Pin = 6;
    const int LEDG_Pin = 3;
    const int LEDB_Pin = 4;
};

#endif
