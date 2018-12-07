#include "TitleScene.h"
#include "../Input/InputManager.h"


namespace
{
	const String ENTER_KEY(L"enter"); // 始めるボタンのキー
	const String EXIT_KEY(L"exit");   // 終えるボタンのキー

	const Point ENTER_BUTTON_POS(420, 300); // 始めるボタンの座標
	const Point EXIT_BUTTON_POS(420, 370);  // 終えるボタンの座標

	const Size  BUTTON_SIZE(160, 70);       // ボタンのサイズ
}


Robot::TitleScene::TitleScene()
{
	InputManager::Instance().clearButtonList();

	InputManager::Instance().registerButton(ENTER_KEY, Rect(ENTER_BUTTON_POS, BUTTON_SIZE));
	InputManager::Instance().registerButton(EXIT_KEY,  Rect(EXIT_BUTTON_POS , BUTTON_SIZE));

	InputManager::Instance().setVerticalAdjacentButton(ENTER_KEY, EXIT_KEY);

	InputManager::Instance().setSelectedButton(ENTER_KEY);
}


void Robot::TitleScene::init()
{

}


void Robot::TitleScene::update()
{
	Optional<String> selectButtonkey = InputManager::Instance().selectButton();
}


void Robot::TitleScene::draw() const
{
	InputManager::Instance().getSelectedButton().getRegion().draw();
}
