#include "GameOverState.h"
#include "../../Input/InputManager.h"


namespace
{
	const int CELL_ALPHA_SPEED = 15; // マスの透明度を1フレームで変更する値
	const int BACK_ALPHA_SPEED = 15; // 背景の透明度を1フレームで変更する値

	const int ALPHA_MAX = 255; // 不透明度の最大値

	const Size CELL_SIZE(40, 40); // 1マスの大きさ

	const int TEXT_DRAW_FRAME_COUNT = 40;      // 振動するフレーム数
	const int SELCT_FRAME_COUNT     = 120;     // 選択肢がでるフレーム数
	const int MAX_TEXT_LENGTH       = 64*6+16; // 文字の長さの最大   

	const int TEXT_DRAW_SPAN = 12; // テキストを表示するフレーム数
	const int CHAR_WIDTH     = 64; // 1文字の幅

	const String RETRY_KEY(L"retry"); // リトライボタンのキー
	const String MENU_KEY (L"menu");  // メニューに戻るボタンのキー

	const Point RETRY_BUTTON_POS(400, 300); // リトライボタンの座標
	const Point MENU_BUTTON_POS(400, 370);  // メニューに戻るボタンの座標
	const Size  BUTTON_SIZE(210, 70);       // ボタンのサイズ
	const Size  BOARD_SIZE(210, 140);       // ボタンを置く板のサイズ
	const int   BOARD_ALPHA = 80;           // ボタンを置く板の不透明度
	const int   CURSOR_WIDTH = 300;         // カーソルの横幅

	const double CURSOR_MOVE_RATE = 0.8; // カーソルが動くときの割合

	const double SHADOW_BLUR_RADIUS = 20.0; // 影のぼかしの大きさ
	const double SHADOW_SPREAD      = 8.0;  // 影の広がりかた
}


Robot::GameOverState::GameOverState()
	: _frameCount(0)
	, _cellColor(Palette::MyBlack, 0)
	, _backColor(Palette::MyWhite, 0)
	, _textDrawRegion(16,112)
{
	InputManager::Instance().clearButtonList();

	InputManager::Instance().registerButton(RETRY_KEY, Rect(RETRY_BUTTON_POS, BUTTON_SIZE));
	InputManager::Instance().registerButton(MENU_KEY , Rect(MENU_BUTTON_POS , BUTTON_SIZE));

	InputManager::Instance().setVerticalAdjacentButton(RETRY_KEY, MENU_KEY);

	InputManager::Instance().setSelectedButton(RETRY_KEY);

	_cursor = InputManager::Instance().getSelectedButton().getRegion();
	_cursor.w = CURSOR_WIDTH;
}


void Robot::GameOverState::update(GameManager & gameManager)
{
	++_frameCount;

	addAlpha(_cellColor, CELL_ALPHA_SPEED);

	if (_frameCount < TEXT_DRAW_FRAME_COUNT) { return; }

	addAlpha(_backColor, BACK_ALPHA_SPEED);

	if (_frameCount%TEXT_DRAW_SPAN == 0)
	{
		_textDrawRegion.x = Min(_textDrawRegion.x + CHAR_WIDTH, MAX_TEXT_LENGTH);
	}

	if (_frameCount < SELCT_FRAME_COUNT) { return; }

	Optional<String> selectButtonkey = InputManager::Instance().selectButton();

	if (selectButtonkey)
	{
		if (*selectButtonkey == RETRY_KEY)
		{
			gameManager.setSceneName(L"LoadGameScene", gameManager.getStageName());
		}
		if (*selectButtonkey == MENU_KEY)
		{
			gameManager.setSceneName(L"MenuScene", L"");
		}
	}

	_cursor.pos = CURSOR_MOVE_RATE*_cursor.pos + (1 - CURSOR_MOVE_RATE)*InputManager::Instance().getSelectedButton().getRegion().pos;
}


void Robot::GameOverState::draw(const GameManager &) const
{
	static const Rect SHAKE_RANGE(-1, -1, 2, 2); // 振動の範囲

	Window::ClientRect().draw(Palette::MyWhite);

	for (int x = 0; x < Window::Width(); x += CELL_SIZE.x)
	{
		for (int y = 0; y < Window::Height(); y += CELL_SIZE.y)
		{
			Rect(Point(x, y) + RandomPoint(SHAKE_RANGE), CELL_SIZE).draw(_cellColor);
		}
	}

	TextureAsset(L"Failed")(Point::Zero, _textDrawRegion).drawAt(Window::Center());

	if (_frameCount < SELCT_FRAME_COUNT) { return; }

	Color boardColor(Palette::MyWhite, BOARD_ALPHA);
	Rect(RETRY_BUTTON_POS, BOARD_SIZE).drawShadow(Vec2::Zero, SHADOW_BLUR_RADIUS, SHADOW_SPREAD, boardColor);

	_cursor.draw(Palette::MyWhite);

	TextureAsset(L"ReTryButton").draw(RETRY_BUTTON_POS);
	TextureAsset(L"MenuButton").draw(MENU_BUTTON_POS);
}


void Robot::GameOverState::addAlpha(Color & color, int addValue)
{
	if (color.a + addValue > ALPHA_MAX)
	{
		color.a = ALPHA_MAX;
		return;
	}

	color.a += addValue;
}
