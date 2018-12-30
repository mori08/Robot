#include "EventManager.h"


Robot::EventManager::EventManager()
{

}


void Robot::EventManager::update()
{
	for (auto & object : _objectList)
	{
		object.second->update();
	}
}

void Robot::EventManager::draw() const
{
	for (const auto & object : _objectList)
	{
		object.second->draw();
	}
}


void Robot::EventManager::generateObject(const String & name, const std::shared_ptr<EventObject>& object)
{
	_objectList[name] = object;
}
