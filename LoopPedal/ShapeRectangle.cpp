#include "ShapeRectangle.h"

ShapeRectangle::ShapeRectangle(Adafruit_ILI9341& display, int16_t x, int16_t y, int16_t w, int16_t h) : 
    Shape(display), x(x), y(y), width(w), height(h) 
{

}

void ShapeRectangle::draw() 
{
    tft.fillRect(x, y, width, height, ILI9341_RED);
}


void ShapeRectangle::erase() 
{
    tft.fillRect(x, y, width, height, ILI9341_BLACK);
}

void ShapeRectangle::update()
{
    // TODO: Implement update logic if necessary
}
