#include "PauseEventState.h"
#include "../../Input/InputManager.h"
#include "../EventManager.h"
#include "PlayEventState.h"


namespace
{
	const Point BUTTON_POS(510, 380); // 一番上のボタンの座標
	const int   BUTTON_WIDTH(200);      // ボタンの幅

	const String CONTINUE_KEY = L"CONTINUE";
	const String SKIP_KEY = L"SKIP";
	const String MENU_KEY = L"MENU";

	const double CURSOR_MOVE_RATE = 0.8; // カーソルが動くときの割合
}


Robot::PauseEventState::PauseEventState()
{
	InputManager::Instance().clearButtonList();

	Rect region(BUTTON_POS, BUTTON_WIDTH, FontAsset(L"15").height);

	InputManager::Instance().registerButton(CONTINUE_KEY, region); region.y += FontAsset(L"15").height;
	InputManager::Instance().registerButton(SKIP_KEY, region    ); region.y += FontAsset(L"15").height;
	InputManager::Instance().registerButton(MENU_KEY, region    );

	InputManager::Instance().setVerticalAdjacentButton(CONTINUE_KEY, SKIP_KEY);
	InputManager::Instance().setVerticalAdjacentButton(SKIP_KEY, MENU_KEY);

	InputManager::Instance().setSelectedButton(CONTINUE_KEY);

	_cursor = InputManager::Instance().getSelectedButton().getRegion();
}


void Robot::PauseEventState::update()
{
	Optional<String> selectButtonKey = InputManager::Instance().selectButton();

	if (InputManager::Instance().option())
	{
		EventManager::Instance().setState(std::make_unique<PlayEventState>());
	}

	if (selectButtonKey)
	{
		if (*selectButtonKey == CONTINUE_KEY)
		{
			EventManager::Instance().setState(std::make_unique<PlayEventState>());
		}
		if (*selectButtonKey == SKIP_KEY)
		{
			EventManager::Instance().changeScene();
		}
		if (*selectButtonKey == MENU_KEY)
		{
			EventManager::Instance().setSceneName(L"MenuScene", L"");
			EventManager::Instance().changeScene();
		}
	}

	_cursor.pos = CURSOR_MOVE_RATE*_cursor.pos + (1 - CURSOR_MOVE_RATE)*InputManager::Instance().getSelectedButton().getRegion().pos;
}


void Robot::PauseEventState::draw() const
{
	EventManager::Instance().drawEventAndObject();

	Window::ClientRect().draw(Color(Palette::MyBlack, 0xC0));

	TextureAsset(L"Pause").drawAt(Window::Center());

	_cursor.draw(Palette::MyWhite);

	int y = BUTTON_POS.y;
	drawButtonName(y, CONTINUE_KEY); y += FontAsset(L"15").height;
	drawButtonName(y, SKIP_KEY);     y += FontAsset(L"15").height;
	drawButtonName(y, MENU_KEY);
}


void Robot::PauseEventState::drawButtonName(int y, const String & name) const
{
	Color color = name == InputManager::Instance().getSelectedButton().getKey() ? Palette::MyBlack : Palette::MyWhite;

	FontAsset(L"15")(name).draw(Window::Width() - FontAsset(L"15")(name).region().w - 10, y, color);
}
