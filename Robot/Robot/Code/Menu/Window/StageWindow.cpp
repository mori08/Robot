#include "StageWindow.h"
#include "../../Input/InputManager.h"
#include "../../SaveData/SaveDataManager.h"


namespace
{
	const Size  BUTTON_SIZE(110, 110); // �{�^���̃T�C�Y
	const Point POS_BASE(15, 100);     // ���W�̊
	const Size  WIDTH(15, 15);         // �{�^���̊Ԋu
	const int   COLUMNS = 5;           // 1�s�ɔz�u����{�^����
	const int   BUTTON_NUM = 10;       // �{�^���̐�
}


Robot::StageWindow::StageWindow()
{
	const Rect TITLE_BUTTON_REGION(16, 16, 168, 56); // �^�C�g���{�^���͈̔�
	
	for (int i = 0; i < BUTTON_NUM; ++i)
	{
		Point pos = POS_BASE;
		pos += Point(i%COLUMNS, i / COLUMNS)*Point(BUTTON_SIZE + WIDTH);

		registerButton(L"Stage" + ToString(i), Rect(pos, BUTTON_SIZE));
	}
	
	registerButton(L"TitleButton", TITLE_BUTTON_REGION);

	_selectedButtonKey = L"Stage0";
}


void Robot::StageWindow::draw() const
{
	drawLight();
	for (const auto & button : _buttonPtrList)
	{
		TextureAsset(button->getKey()).draw(button->getPoint());
		if (button->getKey().includes(L"Stage") && SaveDataManager::Instance().getFlag(button->getKey()))
		{
			TextureAsset(L"Check").draw(button->getPoint());
		}
	}
}


void Robot::StageWindow::updateInputManager() const
{
	InputManager::Instance().clearButtonList();

	for (int i = 0; i < BUTTON_NUM; ++i)
	{
		InputManager::Instance().registerButton(_buttonPtrList[i]);
	}

	for (int i = 0; i < BUTTON_NUM; ++i)
	{
		int verticalId = i - COLUMNS;
		if (verticalId >= 0)
		{
			InputManager::Instance().setVerticalAdjacentButton(_buttonPtrList[verticalId]->getKey(), _buttonPtrList[i]->getKey());
		}

		int horizontalId = (i - 1 + BUTTON_NUM) % BUTTON_NUM;
		InputManager::Instance().setHorizontalAdjacentButton(_buttonPtrList[horizontalId]->getKey(), _buttonPtrList[i]->getKey());
	}

	InputManager::Instance().registerButton(_buttonPtrList[BUTTON_NUM]);

	InputManager::Instance().setSelectedButton(_selectedButtonKey);
}
