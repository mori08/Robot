#include "EventManager.h"


Robot::EventManager::EventManager()
{

}


void Robot::EventManager::update()
{
	for (auto & object : _objectList)
	{
		object.second.update();
	}
}

void Robot::EventManager::draw() const
{
	for (const auto & object : _objectList)
	{
		object.second.draw();
	}
}
