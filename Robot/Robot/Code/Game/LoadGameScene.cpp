#include "LoadGameScene.h"
#include "GameManager.h"

void Robot::LoadGameScene::load()
{
	GameManager::Instance().load(L"Asset/Data/Game/" + m_data->sceneInfo + L".csv");
	GameManager::Instance().setStageName(m_data->sceneInfo);
}


void Robot::LoadGameScene::complete()
{
	changeScene(L"GameScene");
}
