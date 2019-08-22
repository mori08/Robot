#include "PlayEventState.h"
#include "../EventManager.h"


void Robot::PlayEventState::update()
{
	EventManager::Instance().updateEventAndObject();
}


void Robot::PlayEventState::draw() const
{
	EventManager::Instance().drawEventAndObject();
}

