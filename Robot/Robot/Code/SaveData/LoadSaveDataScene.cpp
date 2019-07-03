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
		m_data->sceneInfo = L"Event0";
		changeScene(L"LoadEventScene");
		// ↑Eventのテスト用
		// ↓正規の実装
		/*
		m_data->sceneInfo = L"Test";
		changeScene(L"MenuScene");
		*/ 
		break;

	case SaveDataManager::LoadResult::ERROR:
	default:
		changeScene(L"TitleScene");
		break;
	}
}
