#ifndef _SHAPE_h
#define _SHAPE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

class Shape {
public:
    Shape(Adafruit_ILI9341& display);
    virtual void draw() = 0;
    virtual void erase() = 0;
    virtual void update() = 0;

protected:
    Adafruit_ILI9341& tft;

private:
};

#endif

