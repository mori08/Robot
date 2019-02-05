#include "LoadEventScene.h"
#include "EventManager.h"


void Robot::LoadEventScene::load()
{
	EventManager::Instance().load(L"Asset/Data/Event/" + m_data->sceneInfo + L".csv");
}


void Robot::LoadEventScene::complete()
{
	changeScene(L"EventScene");
}
