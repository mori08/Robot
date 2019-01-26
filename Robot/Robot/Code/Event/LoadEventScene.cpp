#include "LoadEventScene.h"
#include"EventManager.h"


namespace
{
	const int TRANSITINO_TIME_MILLISEC = 2000;
}


void Robot::LoadEventScene::load()
{
	EventManager::Instance().load(L"Asset/Data/Event/" + m_data->sceneInfo + L".csv");
}


void Robot::LoadEventScene::complete()
{
	changeScene(L"EventScene", TRANSITINO_TIME_MILLISEC);
}
