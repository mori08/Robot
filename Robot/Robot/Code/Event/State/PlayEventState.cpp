#include "PlayEventState.h"
#include "../EventManager.h"
#include "PauseEventState.h"
#include "../../Input/InputManager.h"


void Robot::PlayEventState::update()
{
	if (InputManager::Instance().option())
	{
		EventManager::Instance().setState(std::make_unique<PauseEventState>());
	}

	EventManager::Instance().updateEventAndObject();
}


void Robot::PlayEventState::draw() const
{
	EventManager::Instance().drawEventAndObject();
}

