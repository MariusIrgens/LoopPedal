#include "TouchManager.h"

TouchManager::TouchManager()
{
	
}

void TouchManager::setup()
{

}

void TouchManager::loop()
{
    // Checks for touch every frame.
    checkTouch();
}

void TouchManager::checkTouch()
{
    // Check for touch
    TSPoint p = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);

    if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
    {
        std::string message = "X: " + std::to_string(p.x) + ", Y: " + std::to_string(p.y) + ", Z: " + std::to_string(p.z);

        Serial.println(message.c_str());
    }
}