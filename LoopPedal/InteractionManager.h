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
    void loop();  
    void onButton1Pressed(); 
    void onButton2Pressed(); 
    int readPotentiometer();
    void blinkLED(int r, int g, int b);

    static void button1ISR(); // ISR for button 1
    static void button2ISR(); // ISR for button 2

private:
    SystemController* systemController; // Pointer to creator

    // Buttons
    static const int buttonPin1 = 14;
    static const int buttonPin2 = 16;
    static volatile unsigned long lastInterruptTime1;
    static volatile unsigned long lastInterruptTime2;

    // Pot
    static const int potPin = A1;
    int potValue = 0;

    // LED
    const int LEDR_Pin = 5;
    const int LEDG_Pin = 3;
    const int LEDB_Pin = 4;
};

#endif
