#include "EventScene.h"
#include "EventManager.h"


void Robot::EventScene::init()
{

}


void Robot::EventScene::update()
{
	EventManager::Instance().update();

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
