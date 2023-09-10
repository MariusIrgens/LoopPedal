// Envelope.h

#ifndef _ENVELOPE_h
#define _ENVELOPE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <math.h>

class Envelope {
public:
    Envelope(float maxValue = 1.0f, float minValue = 0.0f, float attackTime = 5.0f, float decayTime = 500.0f, float curvedness = 1.0f);

    void start();

    void update(int deltaTime);

    float read() const;

    void setMaxValue(float newMaxValue);

    void setMinValue(float newMinValue);

    void setAttackTime(float newAttackTime); // In ms

    void setDecayTime(float newDecayTime); // In ms

    void setCurvedness(float curve); // 1.0 = linear, less = fast-then-slow, more = slow-then-fast

    bool isActive() const;

private:
    enum class Phase { IDLE, ATTACK, DECAY };
    float maxValue;
    float minValue;
    float value;
    float curvedness;
    Phase currentPhase;
    float attackIncrement;  // how much to increase the value by during the attack phase per deltaTime
    float decayDecrement;   // how much to decrease the value by during the decay phase per deltaTime
    bool active;

    unsigned long decayStartTime;  // in microseconds
    float decayDuration;  // in microseconds
};

#endif

