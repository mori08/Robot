#include "StageWindow.h"
#include "../../Input/InputManager.h"
#include "../../SaveData/SaveDataManager.h"


namespace
{
	const Size  BUTTON_SIZE(110, 110); // ボタンのサイズ
	const Point POS_BASE(15, 100);     // 座標の基準
	const Size  WIDTH(15, 15);         // ボタンの間隔
	const int   COLUMNS = 5;           // 1行に配置するボタン数
	const int   BUTTON_NUM = 10;       // ボタンの数

	const Vec2 OPEN_OFFSET(0, -10);
}


Robot::StageWindow::StageWindow(MenuScene & menuScene)
{
	const Rect TITLE_BUTTON_REGION(16, 16, 168, 56); // タイトルボタンの範囲
	
	for (int i = 0; i < BUTTON_NUM; ++i)
	{
		Point pos = POS_BASE;
		pos += Point(i%COLUMNS, i / COLUMNS)*Point(BUTTON_SIZE + WIDTH);
		String stageName = L"Stage" + ToString(i);

		registerButton
		(
			L"Stage" + ToString(i),
			Rect(pos, BUTTON_SIZE),
			std::make_unique<Processing>
			(
				[&menuScene, stageName]() 
				{ 
					if (SaveDataManager::Instance().getFlag(stageName))
					{
						menuScene.changeSceneAndInfo(L"LoadGameScene" , stageName);
					}
					else
					{
						menuScene.changeSceneAndInfo(L"LoadEventScene", stageName + L"Start");
					}
				}
			)
		);
	}
	setClosedProcessing(std::make_unique<Processing>([&menuScene]() { menuScene.closeWindow(L"Main"); }));

	_selectedButtonKey = L"Stage0";

	_openOffset = OPEN_OFFSET;
}


void Robot::StageWindow::draw() const
{
	MenuWindowBase::draw();
	for (const auto & button : _buttonPtrList)
	{
		if (SaveDataManager::Instance().getFlag(button->getKey()))
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

	InputManager::Instance().setSelectedButton(_selectedButtonKey);
}
