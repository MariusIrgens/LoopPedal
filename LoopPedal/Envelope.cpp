#include "envelope.h"

Envelope::Envelope(float maxValue, float minValue, float attackTime, float decayTime, float curvedness)
    : maxValue(maxValue), minValue(minValue), value(maxValue), curvedness(curvedness), currentPhase(Phase::IDLE), active(false)
{
    setAttackTime(attackTime);
    setDecayTime(decayTime);
}


void Envelope::start() {
    active = true;
    value = minValue;
    currentPhase = Phase::ATTACK;
    decayStartTime = micros();

}

void Envelope::update(int deltaTime) {
    if (active) {
        switch (currentPhase) {
        case Phase::ATTACK:
            value += attackIncrement * (deltaTime / 1e3);  
            if (value >= maxValue) {
                value = maxValue;
                currentPhase = Phase::DECAY;
            }
            break;

        case Phase::DECAY:
        {
            unsigned long elapsedTime = micros() - decayStartTime;
            float lerpFactor = elapsedTime / decayDuration;  // will be in range [0, 1]
            lerpFactor = max(lerpFactor, 0.0f);

            // Adjust the factor based on the desired curve
            float factor = pow(lerpFactor, curvedness);
            float decrementValue = decayDecrement * (deltaTime / 1e3) * factor;

            value -= decrementValue;
            if (value <= minValue) {
                value = minValue;
                active = false;
            }
            break;
        }
        case Phase::IDLE:
            // do nothing
            break;

        default:
            break;
        }
    }
}

float Envelope::read() const {
    return value;
}

void Envelope::setMaxValue(float newMaxValue) {
    maxValue = newMaxValue;
}

void Envelope::setMinValue(float newMinValue) {
    minValue = newMinValue;
}

void Envelope::setAttackTime(float newAttackTime) {
    attackIncrement = (maxValue - minValue) / newAttackTime;
}

void Envelope::setDecayTime(float newDecayTime) {
    decayDecrement = (maxValue - minValue) / newDecayTime;
    decayDuration = newDecayTime * 1e3;  // Convert to microseconds

}

bool Envelope::isActive() const {
    return active;
}
