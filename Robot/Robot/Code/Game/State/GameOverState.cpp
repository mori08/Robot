#include "GameOverState.h"
#include "../../Input/InputManager.h"
#include "../../MyColor.h"


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

	const String RETRY_KEY(L"RETRY"); // リトライボタンのキー
	const String MENU_KEY (L"MENU");  // メニューに戻るボタンのキー
	std::vector<String> KEY_LIST      // キーのリスト
	{
		RETRY_KEY,
		MENU_KEY
	};

	const Point BUTTON_POS(510, 380); // 一番上のボタンの座標
	const int   BUTTON_WIDTH(200);    // ボタンの幅

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

	Rect region(BUTTON_POS, BUTTON_WIDTH, FontAsset(L"15").height);
	for (const auto & key : KEY_LIST)
	{
		InputManager::Instance().registerButton(key, region);
		region.y += FontAsset(L"15").height;
	}

	InputManager::Instance().setVerticalAdjacentButton(RETRY_KEY, MENU_KEY);

	InputManager::Instance().setSelectedButton(RETRY_KEY);

	_cursor = InputManager::Instance().getSelectedButton().getRegion();
}


void Robot::GameOverState::update()
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
			GameManager::Instance().setSceneName(L"LoadGameScene", GameManager::Instance().getStageName());
		}
		if (*selectButtonkey == MENU_KEY)
		{
			GameManager::Instance().setSceneName(L"MenuScene", L"");
		}
	}

	_cursor.pos = CURSOR_MOVE_RATE*_cursor.pos + (1 - CURSOR_MOVE_RATE)*InputManager::Instance().getSelectedButton().getRegion().pos;
}


void Robot::GameOverState::draw() const
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

	Color boardColor(Palette::MyBlack, 0x80);
	Rect(BUTTON_POS, BUTTON_WIDTH, (int)KEY_LIST.size()*FontAsset(L"15").height).drawShadow(Vec2::Zero, SHADOW_BLUR_RADIUS, SHADOW_SPREAD, boardColor);

	_cursor.draw(Palette::MyWhite);

	int y = BUTTON_POS.y;
	for (const auto & key : KEY_LIST)
	{
		Color color = key == InputManager::Instance().getSelectedButton().getKey() ? Palette::MyBlack : Palette::MyWhite;
		FontAsset(L"15")(key).draw(Window::Width() - FontAsset(L"15")(key).region().w - 10, y, color);
		y += FontAsset(L"15").height;
	}
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
