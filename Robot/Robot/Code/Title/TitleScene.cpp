#include "TitleScene.h"
#include "../Input/InputManager.h"


namespace
{
	const String ENTER_KEY(L"enter"); // �n�߂�{�^���̃L�[
	const String EXIT_KEY(L"exit");   // �I����{�^���̃L�[

	const Point ENTER_BUTTON_POS(420, 300); // �n�߂�{�^���̍��W
	const Point EXIT_BUTTON_POS(420, 370);  // �I����{�^���̍��W

	const Size  BUTTON_SIZE(160, 70);       // �{�^���̃T�C�Y
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
