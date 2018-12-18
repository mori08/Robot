#include"LoadDataScene.h"


Robot::LoadDataScene::LoadDataScene()
{
	_isLoading  = true;
	_loadThread = std::thread([this]() {_loadResult = SaveDataManager::Instance().load(); });
}


Robot::LoadDataScene::~LoadDataScene()
{
	if (_isLoading)
	{
		_loadThread.join();
	}
}


void Robot::LoadDataScene::init()
{
	
}


void Robot::LoadDataScene::update()
{
	if (_isLoading&&_loadThread.joinable())
	{
		_loadThread.join();
		_isLoading = false;

		switch (_loadResult)
		{
		case SaveDataManager::LoadResult::NEW_GAME:
			Println(L"NEW_GAME");
			break;
		case SaveDataManager::LoadResult::CONTINUE:
			Println(L"CONTINUE");
			SaveDataManager::Instance().showFlagList();
			break;
		case SaveDataManager::LoadResult::ERROR:
			Println(L"ERROR");
			break;
		}

		return;
	}
}


void Robot::LoadDataScene::draw() const
{

}
