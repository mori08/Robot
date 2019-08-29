#include "LoadMenuScene.h"
#include "MenuManager.h"


void Robot::LoadMenuScene::load()
{
	MenuManager::Instance().load();
}


void Robot::LoadMenuScene::complete()
{
	changeScene(L"MenuScene");
}
