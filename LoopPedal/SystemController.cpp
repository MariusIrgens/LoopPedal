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
	audioManager->loop();
	interactionManager->loop();

	// interactionManager->readPotentiometer() reads the pot
	//std::string message = "pot: " + std::to_string(interactionManager->readPotentiometer());
	//Serial.println(message.c_str());

	delay(100);
}

void SystemController::newSequence()
{
	Serial.println("New sequence!");
}

void SystemController::recordLoop()
{
	Serial.println("Record loop!");
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
		interactionManager->blinkLED(50, 0, 0);
		break;
	case 2:
		//Serial.println("Blink major beat!");
		interactionManager->blinkLED(0, 50, 0);
		break;
	case 3:
		//Serial.println("Blink others!");
		interactionManager->blinkLED(0, 0, 50);
		break;
	default:
		break;
	}
}

