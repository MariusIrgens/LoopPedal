#include "SystemController.h"

SystemController::SystemController()
{
	audioManager = std::make_unique<AudioManager>(this);
	interactionManager = std::make_unique<InteractionManager>(this);
}

void SystemController::setup()
{
	Serial.begin(9600); // Used for debug. Remove when done.
	audioManager->setup();
	interactionManager->setup();
}

void SystemController::loop()
{
	// Only for non-timer critical functions

	// Read pots and update volume if moved
	setAudioVolume();
	setDrumVolume();
	delay(500);
}

void SystemController::setAudioVolume()
{
	float volume = float(interactionManager->readPotentiometer(1)) / 1023.0f;
	audioManager->setAudioVolume(volume);
}

void SystemController::setDrumVolume()
{
	float volume = float(interactionManager->readPotentiometer(2)) / 1023.0f;
	audioManager->setDrumVolume(volume);
}

void SystemController::newSequence()
{
	Serial.println("New sequence!");
	audioManager->getLooper()->reset();
}

void SystemController::recordLoop()
{
	audioManager->getLooper()->record();
}

void SystemController::blinkLED(int state)
{
	switch (state)
	{
	case 0:
		interactionManager->blinkLED(0, 0, 0);
		break;
	case 1:
		//Serial.println("Blink seq start!");
		interactionManager->blinkLED(LEDSTRENGTH, 0, 0);
		break;
	case 2:
		//Serial.println("Blink major beat!");
		interactionManager->blinkLED(0, LEDSTRENGTH, 0);
		break;
	case 3:
		//Serial.println("Blink others!");
		interactionManager->blinkLED(0, 0, LEDSTRENGTH);
		break;
	default:
		break;
	}
}

