#include"LoadSaveDataScene.h"
#include"../Menu/MenuManager.h"


void Robot::LoadSaveDataScene::load()
{
	_loadResult = SaveDataManager::Instance().load();
}


void Robot::LoadSaveDataScene::complete()
{
	switch(_loadResult)
	{
	case SaveDataManager::LoadResult::NEW_GAME:
		SaveDataManager::Instance().initOfNewGame();
		m_data->sceneInfo = L"Stage0Start";
		changeScene(L"LoadEventScene");
		break;

	case SaveDataManager::LoadResult::CONTINUE:		
		m_data->sceneInfo = L"";
		changeScene(L"LoadMenuScene");
		break;

	case SaveDataManager::LoadResult::ERROR:
	default:
		changeScene(L"TitleScene");
		break;
	}
}
