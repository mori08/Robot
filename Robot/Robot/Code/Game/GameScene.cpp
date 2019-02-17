#include "GameScene.h"
#include "GameManager.h"


namespace
{
	const int TRANSMISSINO_TIME = 2000; // �V�[���J�ڂɂ����鎞��(ms)
}


void Robot::GameScene::update()
{
	GameManager::Instance().update();

	if (GameManager::Instance().isChangeAbleScene(changeSceneName, m_data->sceneInfo))
	{
		changeScene(changeSceneName,TRANSMISSINO_TIME);
	}
}


void Robot::GameScene::draw() const
{
	GameManager::Instance().draw();
}
