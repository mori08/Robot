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

#ifdef _DEBUG
	if (Input::Key0.clicked)
	{
		changeScene(L"TitleScene");
	}
#endif // _DEBUG

}


void Robot::EventScene::draw() const
{
	EventManager::Instance().draw();
}
