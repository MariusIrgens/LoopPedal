// TouchManager.h

#ifndef _TOUCHMANAGER_h
#define _TOUCHMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <string>
#include <TouchScreen.h>

// PINS

#define YP A2  // Y+ 
#define XM A3  // X-
#define YM 3   // Y-
#define XP 2   // X+

// TOUCH PRESSURE

#define MINPRESSURE 10
#define MAXPRESSURE 1000

class TouchManager {
public:
	TouchManager();
	void setup();
	void loop();
	void checkTouch();

private:
	TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

};

#endif

