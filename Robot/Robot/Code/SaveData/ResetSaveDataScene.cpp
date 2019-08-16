#include "ResetSaveDataScene.h"
#include "SaveDataManager.h"


void Robot::ResetSaveDataScene::load()
{
	SaveDataManager::Instance().initOfNewGame();
}


void Robot::ResetSaveDataScene::complete()
{
	changeScene(L"SavingDataScene");
}
