#include "MainWindow.h"
#include "../../Input/InputManager.h"


namespace
{
	const String STAGE_KEY(L"STAGE SELECT"); // ステージボタンのキー
	const String TITLE_KEY(L"TITLE");        // タイトルボタンのキー

	const Point BUTTON_POS(0, 40); // 一番上のボタンの座標
	const int   BUTTON_WIDTH(180); // ボタンの鼻

	const Vec2 OPEN_OFFSET(-10, 0);
}


Robot::MainWindow::MainWindow(MenuScene & menuScene)
{
	Rect region(BUTTON_POS, BUTTON_WIDTH, FontAsset(L"15").height);

	_cursor = region;

	registerButton
	(
		STAGE_KEY,
		region,
		std::make_unique<Processing>([&menuScene]() { menuScene.openWindow(L"Stage"); })
	);
	region.y += FontAsset(L"15").height;
	registerButton
	(
		TITLE_KEY,
		region,
		std::make_unique<Processing>([&menuScene]() { menuScene.changeSceneAndInfo(L"TitleScene", L""); })
	); 

	_selectedButtonKey = STAGE_KEY;

	_openOffset = OPEN_OFFSET;
}


void Robot::MainWindow::updateInputManager() const
{
	InputManager::Instance().clearButtonList();

	for (const auto & button : _buttonPtrList)
	{
		InputManager::Instance().registerButton(button->getKey(), button->getRegion());
	}

	InputManager::Instance().setVerticalAdjacentButton(STAGE_KEY, TITLE_KEY);

	InputManager::Instance().setSelectedButton(_selectedButtonKey);
}
