#include "SceneEvent.h"


namespace
{
	const size_t INFO_SIZE = 2; // 詳細の配列のサイズ

	const size_t SCENE_NAME = 0; // シーン名のインデックス
	const size_t SCENE_INFO = 1; // 遷移先のシーンで用いる補足情報のインデックス
}


bool Robot::SceneEvent::load(const Info & info)
{
	if (info.size() != INFO_SIZE)
	{
		printError(L"引数のサイズが違います");
		printError(L"検出値 : " + ToString(info.size()) + L" , 期待値 : " + ToString(INFO_SIZE));
		return false;
	}

	_sceneName = info[SCENE_NAME];
	_sceneInfo = info[SCENE_INFO];

	return _isSuccess = true;
}


void Robot::SceneEvent::perform() const
{
	EventManager::Instance().setSceneName(_sceneName, _sceneInfo);
}

bool Robot::SceneEvent::isCompleted() const
{
	return true;
}
