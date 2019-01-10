#include "EventScene.h"
#include "EventManager.h"


void Robot::EventScene::init()
{

}


void Robot::EventScene::update()
{
	EventManager::Instance().update();
}


void Robot::EventScene::draw() const
{
	EventManager::Instance().draw();
}
