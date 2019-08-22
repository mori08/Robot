#include "PauseGameState.h"
#include "PlayingState.h"
#include "../../Input/InputManager.h"
#include "../../MyColor.h"


namespace
{
	const Point BUTTON_POS  (510, 380); // 一番上のボタンの座標
	const int   BUTTON_WIDTH(200);      // ボタンの幅

	const String CONTINUE_KEY = L"CONTINUE";
	const String RETRY_KEY    = L"RETRY";
	const String MENU_KEY     = L"MENU";

	const double CURSOR_MOVE_RATE = 0.8; // カーソルが動くときの割合
}


Robot::PauseGameState::PauseGameState()
{
	InputManager::Instance().clearButtonList();

	Rect region(BUTTON_POS, BUTTON_WIDTH, FontAsset(L"15").height);

	InputManager::Instance().registerButton(CONTINUE_KEY, region); region.y += FontAsset(L"15").height;
	InputManager::Instance().registerButton(RETRY_KEY   , region); region.y += FontAsset(L"15").height;
	InputManager::Instance().registerButton(MENU_KEY    , region);

	InputManager::Instance().setVerticalAdjacentButton(CONTINUE_KEY, RETRY_KEY);
	InputManager::Instance().setVerticalAdjacentButton(RETRY_KEY   , MENU_KEY );

	InputManager::Instance().setSelectedButton(CONTINUE_KEY);

	_cursor = InputManager::Instance().getSelectedButton().getRegion();
}


void Robot::PauseGameState::update()
{
	Optional<String> selectButtonKey = InputManager::Instance().selectButton();

	if (selectButtonKey)
	{
		if (*selectButtonKey == CONTINUE_KEY)
		{
			GameManager::Instance().changeGameState(std::make_unique<PlayingState>());
		}
		if (*selectButtonKey == RETRY_KEY)
		{
			GameManager::Instance().setSceneName(L"LoadGameScene", GameManager::Instance().getStageName());
		}
		if (*selectButtonKey == MENU_KEY)
		{
			GameManager::Instance().setSceneName(L"MenuScene", L"");
		}
	}

	_cursor.pos = CURSOR_MOVE_RATE*_cursor.pos + (1 - CURSOR_MOVE_RATE)*InputManager::Instance().getSelectedButton().getRegion().pos;
}


void Robot::PauseGameState::draw() const
{
	TextureAsset(L"Pause").drawAt(Window::Center());

	_cursor.draw(Palette::MyWhite);

	int y  = BUTTON_POS.y;
	drawButtonName(y, CONTINUE_KEY); y += FontAsset(L"15").height;
	drawButtonName(y, RETRY_KEY);    y += FontAsset(L"15").height;
	drawButtonName(y, MENU_KEY);
}


void Robot::PauseGameState::drawButtonName(int y, const String & name) const
{
	Color color = name == InputManager::Instance().getSelectedButton().getKey() ? Palette::MyBlack : Palette::MyWhite;
	
	FontAsset(L"15")(name).draw(Window::Width() - FontAsset(L"15")(name).region().w - 10, y, color);
}
