#include "PlayingState.h"


void Robot::PlayingState::update(GameManager & gameManager)
{
	gameManager.updateObjectAndLight();
}


void Robot::PlayingState::draw(const GameManager & gameManager) const
{
	gameManager.drawObjectAndLight();
}
