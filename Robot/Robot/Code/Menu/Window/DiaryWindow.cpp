#include "DiaryWindow.h"
#include "../../SaveData/SaveDataManager.h"
#include "../../Input/InputManager.h"
#include "../../MyColor.h"


namespace
{
	const int MAX_STAGE_NUM = 10; // ステージ数の最大値

	const int   STAGE_WIDTH (90);
	const Point STAGE_POS   (210, 40);
	const Point A_BUTTON_POS = STAGE_POS + Point(STAGE_WIDTH, 0);

	const Vec2 OPEN_OFFSET(-10, 0);
}


Robot::DiaryWindow::DiaryWindow(MenuScene & menuScene)
{
	Rect regionA(A_BUTTON_POS, FontAsset(L"15")(L" [ A ] ").region().w, FontAsset(L"15").height);
	Rect regionB = regionA;
	regionB.x += FontAsset(L"15")(L" [ A ] ").region().w;
	regionB.w  = FontAsset(L"15")(L" [ B ] ").region().w;

	_cursor = regionA;

	for (int i = 0; i < MAX_STAGE_NUM; ++i)
	{
		String eventName = L"Stage" + ToString(i);

		if (!SaveDataManager::Instance().getFlag(eventName)) { break; }

		// スタートイベント
		registerButton
		(
			eventName + L"Start",
			regionA,
			std::make_unique<Processing>
			(
				[&menuScene, eventName]()
				{
					menuScene.changeSceneAndInfo(L"LoadDiaryScene", eventName + L"Start");
				}
			)
		);
		setButtonName(eventName + L"Start", L"[ A ]");

		// エンドイベント
		registerButton
		(
			eventName + L"End",
			regionB,
			std::make_unique<Processing>
			(
				[&menuScene, eventName]()
				{
					menuScene.changeSceneAndInfo(L"LoadDiaryScene", eventName + L"End");
				}
			)
		);
		setButtonName(eventName + L"End", L"[ B ]");

		regionA.y += FontAsset(L"15").height;
		regionB.y += FontAsset(L"15").height;
		_stageNum = i + 1;
	}
	setClosedProcessing(std::make_unique<Processing>([&menuScene]() { menuScene.closeWindow(L"Main"); }));

	_selectedButtonKey = L"Stage0Start";

	_openOffset = OPEN_OFFSET;
}


void Robot::DiaryWindow::draw() const
{
	MenuWindowBase::draw();

	Point pos = STAGE_POS;
	for (int i = 0; i < _stageNum; ++i)
	{
		Rect(pos, STAGE_WIDTH, FontAsset(L"15").height).draw(_boardColor);
		FontAsset(L"15")(L" Stage" + ToString(i)).draw(pos, _white);
		pos.y += FontAsset(L"15").height;
	}
}


void Robot::DiaryWindow::updateInputManager() const
{
	InputManager::Instance().clearButtonList();

	for (const auto & button : _buttonPtrList)
	{
		InputManager::Instance().registerButton(button->getKey(), button->getRegion());
	}

	for (int i = 0; i < _stageNum; ++i)
	{
		String stageName = L"Stage" + ToString(i);
		
		InputManager::Instance().setHorizontalAdjacentButton(stageName + L"Start", stageName + L"End");

		if (i != 0)
		{
			String verticalName = L"Stage" + ToString(i - 1);
			InputManager::Instance().setVerticalAdjacentButton(verticalName + L"Start", stageName + L"Start");
			InputManager::Instance().setVerticalAdjacentButton(verticalName + L"End"  , stageName + L"End");
		}
	}

	InputManager::Instance().setSelectedButton(_selectedButtonKey);
}
