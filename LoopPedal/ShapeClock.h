#ifndef _SHAPECLOCK_h
#define _SHAPECLOCK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Shape.h"

#define CIRCLE_THICKNESS 10

class ShapeClock : public Shape {
public:
    ShapeClock(Adafruit_ILI9341& display, int16_t x, int16_t y, int16_t r);

    void draw() override;
    void erase() override;
    void update() override;

private:
    int16_t xCenter, yCenter, radius, pointerLength;
    float angle = 0.0;
    const float deltaAngle = PI / 60;
};


#endif

