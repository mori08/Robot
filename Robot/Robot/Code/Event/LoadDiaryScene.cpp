#include "LoadDiaryScene.h"
#include "EventManager.h"


void Robot::LoadDiaryScene::load()
{
	EventManager::Instance().setName(m_data->sceneInfo);
	EventManager::Instance().load(L"Asset/Data/Event/" + m_data->sceneInfo + L".csv");
	EventManager::Instance().setSceneName(L"MenuScene", L"");
}


void Robot::LoadDiaryScene::complete()
{
	changeScene(L"EventScene");
}

