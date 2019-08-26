#include "PlayingState.h"
#include "../../Input/InputManager.h"
#include "PauseGameState.h"


void Robot::PlayingState::update()
{
	if (InputManager::Instance().option())
	{
		GameManager::Instance().pause();
	}

	GameManager::Instance().updateObjectAndLight();
}


void Robot::PlayingState::draw() const
{
	GameManager::Instance().drawObjectAndLight();
}
