#include "StageWindow.h"
#include "../MenuManager.h"
#include "../../Input/InputManager.h"
#include "../../SaveData/SaveDataManager.h"
#include "../../MyColor.h"


namespace
{
	const int   MAX_BUTTON_NUM = 10;   // ƒ{ƒ^ƒ“‚Ì”‚ÌÅ‘å’l

	const Point BUTTON_POS(210, 40);
	const int   BUTTON_WIDTH(200);

	const Point NEW_POS(90,0);

	const Vec2 OPEN_OFFSET(-10, 0);
}


Robot::StageWindow::StageWindow()
{	
	_openOffset = OPEN_OFFSET;
}


void Robot::StageWindow::draw() const
{
	MenuWindowBase::draw();
	for (const auto & button : _buttonPtrList)
	{
		if (SaveDataManager::Instance().getFlag(button->getKey())) { continue; }

		ColorF color = _selectedButtonKey == button->getKey() ? _boardColor : _white;
		FontAsset(L"15")(L"[NEW]").draw(button->getPoint() + NEW_POS, color);
	}
}


void Robot::StageWindow::updateInputManager() const
{
	InputManager::Instance().clearButtonList();

	for (int i = 0; i < _buttonNum; ++i)
	{
		InputManager::Instance().registerButton(_buttonPtrList[i]);
	}

	for (int i = 1; i < _buttonNum; ++i)
	{
		int horizontalId = (i - 1 + MAX_BUTTON_NUM) % MAX_BUTTON_NUM;
		if (horizontalId < _buttonNum)
		{
			InputManager::Instance().setVerticalAdjacentButton(_buttonPtrList[horizontalId]->getKey(), _buttonPtrList[i]->getKey());
		}
	}

	InputManager::Instance().setSelectedButton(_selectedButtonKey);
}


void Robot::StageWindow::makeButton()
{
	Rect region(BUTTON_POS, BUTTON_WIDTH, FontAsset(L"15").height);

	for (int i = 0; i < MAX_BUTTON_NUM; ++i)
	{
		String stageName = L"Stage" + ToString(i);

		registerButton
		(
			stageName,
			region,
			std::make_unique<Processing>
			(
				[stageName]() 
				{ 
					if (SaveDataManager::Instance().getFlag(stageName))
					{
						MenuManager::Instance().setSceneName(L"LoadGameScene" , stageName);
					}
					else
					{
						MenuManager::Instance().setSceneName(L"LoadEventScene", stageName + L"Start");
					}
				}
			)
		);
		_defaultButton = { stageName,region };

		region.y += FontAsset(L"15").height;
		_buttonNum = i + 1;

		if (!SaveDataManager::Instance().getFlag(stageName))
		{
			break;
		}
	}
	setClosedProcessing(std::make_unique<Processing>([]() { MenuManager::Instance().closeWindow(L"Main"); }));

}
