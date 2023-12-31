#ifndef _SYSTEMCONTROLLER_h
#define _SYSTEMCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <memory>
#include <string>

#include "AudioManager.h"
#include "InteractionManager.h"

#define FRAMERATE 30
#define LEDSTRENGTH 10

class SystemController {
public:
	SystemController();
	void setAudioVolume();
	void setDrumVolume();
	void newSequence();
	void record();
	void blinkLED(int state);
	void lightRecLED(int state);
	void setup();
	void loop();
	void incrementBPM(int direction);
	void shouldChange(bool shouldChange);

	std::unique_ptr<AudioManager> audioManager;
	std::unique_ptr<InteractionManager> interactionManager;

};
#endif

