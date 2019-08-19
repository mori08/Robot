#include "PlayingState.h"


void Robot::PlayingState::update()
{
	GameManager::Instance().updateObjectAndLight();
}


void Robot::PlayingState::draw() const
{
	GameManager::Instance().drawObjectAndLight();
}
