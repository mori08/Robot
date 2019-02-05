#include "LoadGameScene.h"
#include "GameManager.h"

void Robot::LoadGameScene::load()
{
	GameManager::Instance().load(L"Asset/Data/Game/" + m_data->sceneInfo + L".csv");
}


void Robot::LoadGameScene::complete()
{
	changeScene(L"GameScene");
}
