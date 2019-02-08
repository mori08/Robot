#include "GameScene.h"
#include "GameManager.h"


void Robot::GameScene::update()
{
	GameManager::Instance().update();
}


void Robot::GameScene::draw() const
{
	GameManager::Instance().draw();
}
