#ifndef _DISPLAYMANAGER_h
#define _DISPLAYMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <TouchScreen.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <vector>
#include <memory>

#include "Shape.h"
#include "ShapeRectangle.h"
#include "ShapeClock.h"

// PINS

#define TFT_DC 9
#define TFT_CS 10
#define YP A2  // Y+ 
#define XM A3  // X-
#define YM 3   // Y-
#define XP 2   // X+

// TOUCH PRESSURE

#define MINPRESSURE 10
#define MAXPRESSURE 1000

// SCREENSIZE
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

// Add static shapes to static list, and dynamic shapes to dynamic list.
// Only update dynamic shapes on each frame call.
// Use FRAMERATE for all calculations? Maybe better to get audio information.

class DisplayManager {
public:
    DisplayManager();
    void setup();
    void loop();
    void checkTouch();
    void drawMainMenu();
    void drawStaticShapes();
    void updateDynamicShapes();

    template <typename T, typename... Args>
    void addStaticShape(Args&&... args);

    template <typename T, typename... Args>
    void addDynamicShape(Args&&... args);

private:
    Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
    TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

    std::vector<std::unique_ptr<Shape>> staticShapes;
    std::vector<std::unique_ptr<Shape>> dynamicShapes;

};

#endif

