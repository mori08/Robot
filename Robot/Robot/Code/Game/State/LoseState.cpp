#include "LoseState.h"
#include "../../SaveData/SaveDataManager.h"


namespace
{
	const int CELL_ALPHA_SPEED = 15; // マスの透明度を1フレームで変更する値
	const int BACK_ALPHA_SPEED = 15; // 背景の透明度を1フレームで変更する値

	const int ALPHA_MAX = 255; // 不透明度の最大値

	const Size CELL_SIZE(40, 40); // 1マスの大きさ

	const int TEXT_DRAW_FRAME_COUNT = 40;      // テキストを表示し始めるフレーム数
	const int SCENE_FRAME_COUNT     = 360;     // シーン遷移するフレーム数

	const int TEXT_DRAW_SPAN = 12; // テキストを表示するフレーム数
	const int CHAR_WIDTH     = 64; // 1文字の幅
}


Robot::LoseState::LoseState()
	: _frameCount(0)
	, _cellColor(Palette::MyBlack, 0)
	, _backColor(Palette::MyWhite, 0)
	,_textDrawRegion(16, 112)
{
}


void Robot::LoseState::update(GameManager & gameManager)
{
	++_frameCount;

	addAlpha(_cellColor, CELL_ALPHA_SPEED);

	if (_frameCount < TEXT_DRAW_FRAME_COUNT) { return; }

	addAlpha(_backColor, BACK_ALPHA_SPEED);

	if (_frameCount%TEXT_DRAW_SPAN == 0)
	{
		_textDrawRegion.x += CHAR_WIDTH;
	}

	if (_frameCount < SCENE_FRAME_COUNT) { return; }

	if (SaveDataManager::Instance().getFlag(gameManager.getStageName()))
	{
		gameManager.setSceneName(L"SavingDataScene", L"");
	}
	else
	{
		gameManager.setSceneName(L"LoadEventScene", gameManager.getStageName() + L"End");
	}

	SaveDataManager::Instance().setFlag(gameManager.getStageName(), true);
}


void Robot::LoseState::draw(const GameManager &) const
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
}

void Robot::LoseState::addAlpha(Color & color, int addValue)
{
	if (color.a + addValue > ALPHA_MAX)
	{
		color.a = ALPHA_MAX;
		return;
	}

	color.a += addValue;
}
