#ifndef _SHAPERECTANGLE_h
#define _SHAPERECTANGLE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Shape.h"

class ShapeRectangle : public Shape {
public:
    ShapeRectangle(Adafruit_ILI9341& display, int16_t x, int16_t y, int16_t w, int16_t h);

    void draw() override;
    void erase() override;
    void update() override;

protected:

private:
    int16_t x, y, width, height;
};

#endif

