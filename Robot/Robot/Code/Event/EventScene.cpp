#include "EventScene.h"
#include "EventManager.h"


void Robot::EventScene::init()
{

}


void Robot::EventScene::update()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isChangeAbleScene(changeSceneName, m_data->sceneInfo))
	{
		changeScene(changeSceneName);
	}
}


void Robot::EventScene::updateFadeIn(double)
{
	EventManager::Instance().updateEventObject();
}


void Robot::EventScene::updateFadeOut(double)
{
	EventManager::Instance().updateEventObject();
}


void Robot::EventScene::draw() const
{
	EventManager::Instance().draw();
}
