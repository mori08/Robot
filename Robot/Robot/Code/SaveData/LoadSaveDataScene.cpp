#include"LoadSaveDataScene.h"


void Robot::LoadSaveDataScene::load()
{
	_loadResult = SaveDataManager::Instance().load();
}


void Robot::LoadSaveDataScene::complete()
{
	switch(_loadResult)
	{
	case SaveDataManager::LoadResult::NEW_GAME:
	case SaveDataManager::LoadResult::CONTINUE:
	case SaveDataManager::LoadResult::ERROR   :
		changeScene(L"TitleScene");
		break;
	default:
		changeScene(L"TitleScene");
		break;
	}
}
