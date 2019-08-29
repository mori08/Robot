#include "MainWindow.h"
#include "../MenuManager.h"
#include "../../Input/InputManager.h"
#include "../../SaveData/SaveDataManager.h"


namespace
{
	const String STAGE_KEY(L"STAGE SELECT"); // �X�e�[�W�{�^���̃L�[
	const String DIARY_KEY(L"DIARY");        // ���L�{�^���̃L�[
	const String TITLE_KEY(L"TITLE");        // �^�C�g���{�^���̃L�[

	const String TITLE_COPY(L"TITLE_COPY"); // �^�C�g���{�^���̃L�[(TITLE_KEY�Ƃ͈ʒu���قȂ�)

	const Point BUTTON_POS(0, 40); // ��ԏ�̃{�^���̍��W
	const int   BUTTON_WIDTH(180); // �{�^���̕@

	const Vec2 OPEN_OFFSET(-10, 0);
}


Robot::MainWindow::MainWindow()
{
	_openOffset = OPEN_OFFSET;
}


void Robot::MainWindow::updateInputManager() const
{
	InputManager::Instance().clearButtonList();

	for (const auto & button : _buttonPtrList)
	{
		InputManager::Instance().registerButton(button->getKey(), button->getRegion());
	}

	for (int i = 1; i < _buttonPtrList.size(); ++i)
	{
		InputManager::Instance().setVerticalAdjacentButton(_buttonPtrList[i - 1]->getKey(), _buttonPtrList[i]->getKey());
	}

	InputManager::Instance().setSelectedButton(_selectedButtonKey);
}


void Robot::MainWindow::makeButton()
{
	Rect region(BUTTON_POS, BUTTON_WIDTH, FontAsset(L"15").height);

	_defaultButton = { STAGE_KEY,region };

	// �X�e�[�W�{�^��
	registerButton
	(
		STAGE_KEY,
		region,
		std::make_unique<Processing>([]() { MenuManager::Instance().openWindow(L"Stage"); })
	);
	region.y += FontAsset(L"15").height;

	// ���L�{�^��
	if (SaveDataManager::Instance().getFlag(L"Stage0"))
	{
		registerButton
		(
			DIARY_KEY,
			region,
			std::make_unique<Processing>([]() { MenuManager::Instance().openWindow(L"Diary"); })
		);
		region.y += FontAsset(L"15").height;

		// �^�C�g���{�^��
		registerButton
		(
			TITLE_KEY,
			region,
			std::make_unique<Processing>([]() { MenuManager::Instance().setSceneName(L"TitleScene", L""); })
		);
	}
	else
	{
		// �^�C�g���{�^��
		registerButton
		(
			TITLE_COPY,
			region,
			std::make_unique<Processing>([]() { MenuManager::Instance().setSceneName(L"TitleScene", L""); })
		);
		_buttonNameMap[TITLE_COPY] = TITLE_KEY;
	}
}
