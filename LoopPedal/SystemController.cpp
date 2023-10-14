#include "SystemController.h"

SystemController::SystemController()
{
	audioManager = std::make_unique<AudioManager>(this);
	interactionManager = std::make_unique<InteractionManager>(this);
}

void SystemController::setup()
{
	Serial.begin(9600); // Used for debug. Remove when done.
	audioManager->getLooper()->setup();
	audioManager->setup();
	interactionManager->setup();
}

void SystemController::loop()
{
	// Read pots and update volume if moved
	setAudioVolume();
	setDrumVolume();
	audioManager->looperLoop();
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
	audioManager->newSequence();
}

void SystemController::record()
{
	audioManager->getLooper()->recordButton();
}

void SystemController::blinkLED(int state)
{
	switch (state)
	{
	case 0:
		interactionManager->blinkLED(0, 0, 0);
		break;
	case 1:
		// Sequence start
		interactionManager->blinkLED(LEDSTRENGTH, LEDSTRENGTH, LEDSTRENGTH);
		break;
	case 2:
		// Major beats
		interactionManager->blinkLED(LEDSTRENGTH, LEDSTRENGTH, 0);
		break;
	case 3:
		// All other beats
		interactionManager->blinkLED(0, LEDSTRENGTH, 0);
		break;
	default:
		break;
	}
}

void SystemController::lightRecLED(int state)
{
	switch (state)
	{
	case 0:
		interactionManager->lightRecLED(0, 0);
		break;
	case 1:
		interactionManager->lightRecLED(LEDSTRENGTH, 0);
		break;
	case 2:
		interactionManager->lightRecLED(0, LEDSTRENGTH);
		break;
	default:
		break;
	}
}

void SystemController::incrementBPM(int amount)
{
	uint32_t currentBPM = audioManager->getCurrentBPM();
	currentBPM += amount;
	audioManager->setCurrentBPM(currentBPM);
	uint32_t newSixteenthNote = audioManager->generateSixteenthFromBPM(currentBPM);
	audioManager->setDrumTimerInterval(newSixteenthNote);
}

void SystemController::shouldChange(bool shouldChange)
{
	if (shouldChange)
		audioManager->getSequencer()->setShouldChange(true);
	else
		audioManager->getSequencer()->setShouldChange(false);
}