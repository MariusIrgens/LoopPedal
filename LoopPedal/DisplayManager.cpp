#include "DisplayManager.h"

DisplayManager::DisplayManager()
{

}

void DisplayManager::setup()
{
    tft.begin();
    tft.setRotation(2);
    tft.fillScreen(ILI9341_BLACK);
    drawMainMenu();
}

void DisplayManager::loop()
{
    // this function will check for touch, and if touched, call a function that draws a complete menu based on the touch and the current menu.
    // It could also just call a function that makes some other selection (like bpm, options, etc).
    // It will also update all animated shapes.
    // It will also call functionality in audioManager


    checkTouch();
    //updateDynamicShapes();

}

void DisplayManager::checkTouch()
{
    // Check for touch
    TSPoint p = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);

    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) 
    {
        //Serial.println(p.z);
    }
}

void DisplayManager::drawMainMenu()
{
    tft.fillScreen(ILI9341_BLACK);

    //addStaticShape<ShapeRectangle>(10, 10, 50, 50);
    //addStaticShape<ShapeRectangle>(SCREEN_WIDTH - 60, 10, 50, 50);
    //addStaticShape<ShapeRectangle>(10, SCREEN_HEIGHT - 60, 50, 50);
    //addStaticShape<ShapeRectangle>(SCREEN_WIDTH - 60, SCREEN_HEIGHT - 60, 50, 50);
    addDynamicShape<ShapeClock>(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 100);
    drawStaticShapes();
}

template <typename T, typename... Args>
void DisplayManager::addStaticShape(Args&&... args)
{
    staticShapes.push_back(std::make_unique<T>(tft, std::forward<Args>(args)...));
}

template <typename T, typename... Args>
void DisplayManager::addDynamicShape(Args&&... args) {
    dynamicShapes.push_back(std::make_unique<T>(tft, std::forward<Args>(args)...));
}


void DisplayManager::drawStaticShapes() 
{
    for (auto& shape : staticShapes) {
        shape->draw();
    }
}

void DisplayManager::updateDynamicShapes() {
    for (auto& shape : dynamicShapes) {
        shape->update();
    }
}
