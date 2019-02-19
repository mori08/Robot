#include "MainWindow.h"
#include "../../Input/InputManager.h"


namespace
{
	const Point STAGE_POS(16, 16);  // �X�e�[�W�{�^���̍��W
	const Point TITLE_POS(200, 16); // �^�C�g���{�^���̍��W

	const Size BUTTON_SIZE(168, 56); // �{�^���̃T�C�Y
}


Robot::MainWindow::MainWindow()
{
	registerButton(L"Stage", Rect(STAGE_POS, BUTTON_SIZE));
	registerButton(L"Title", Rect(TITLE_POS, BUTTON_SIZE));

	_selectedButtonKey = L"Stage";
}


void Robot::MainWindow::draw() const
{
	drawLight();

	TextureAsset(L"StageButton").draw(STAGE_POS);
	TextureAsset(L"TitleButton").draw(TITLE_POS);
}


void Robot::MainWindow::updateInputManager() const
{
	InputManager::Instance().clearButtonList();

	InputManager::Instance().registerButton(L"Stage", Rect(STAGE_POS, BUTTON_SIZE));
	InputManager::Instance().registerButton(L"Title", Rect(TITLE_POS, BUTTON_SIZE));

	InputManager::Instance().setHorizontalAdjacentButton(L"Stage", L"Title");

	InputManager::Instance().setSelectedButton(_selectedButtonKey);
}
