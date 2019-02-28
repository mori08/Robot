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
	registerButton(L"StageButton", Rect(STAGE_POS, BUTTON_SIZE));
	registerButton(L"TitleButton", Rect(TITLE_POS, BUTTON_SIZE));

	_selectedButtonKey = L"StageButton";
}


void Robot::MainWindow::updateInputManager() const
{
	InputManager::Instance().clearButtonList();

	InputManager::Instance().registerButton(L"StageButton", Rect(STAGE_POS, BUTTON_SIZE));
	InputManager::Instance().registerButton(L"TitleButton", Rect(TITLE_POS, BUTTON_SIZE));

	InputManager::Instance().setHorizontalAdjacentButton(L"StageButton", L"TitleButton");

	InputManager::Instance().setSelectedButton(_selectedButtonKey);
}
