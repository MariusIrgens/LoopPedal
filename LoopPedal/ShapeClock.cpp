#include "ShapeClock.h"

ShapeClock::ShapeClock(Adafruit_ILI9341& display, int16_t x, int16_t y, int16_t r)
    : Shape(display), xCenter(x), yCenter(y), radius(r)
{
    pointerLength = radius - CIRCLE_THICKNESS;  // Set pointer length to inner radius

    // Drawing the circle with thickness
    tft.fillCircle(xCenter, yCenter, radius, ILI9341_RED);
    tft.fillCircle(xCenter, yCenter, pointerLength, ILI9341_BLACK);
}

void ShapeClock::draw() {
    // Drawing the pointer
    int16_t xEnd = xCenter + pointerLength * cos(angle);
    int16_t yEnd = yCenter + pointerLength * sin(angle);
    tft.drawLine(xCenter, yCenter, xEnd, yEnd, ILI9341_WHITE);
}

void ShapeClock::erase() {
    // Only erasing the pointer, since circle remains static
    int16_t xEnd = xCenter + pointerLength * cos(angle);
    int16_t yEnd = yCenter + pointerLength * sin(angle);
    tft.drawLine(xCenter, yCenter, xEnd, yEnd, ILI9341_BLACK);
}

void ShapeClock::update() {
    erase();   // Erase the current pointer
    angle += deltaAngle;  // Update the angle
    if (angle >= 2 * PI) angle -= 2 * PI;  // Reset angle after one full rotation
    draw();   // Draw the updated pointer
}
