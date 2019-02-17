#include "GameClearState.h"


namespace
{
	const int BACK_ALPHA_SPEED  = 15;  // 背景の透明度を1フレームで変更する値
	const int LIGHT_ALPHA_SPEED = 25;  // 光の透明度を1フレームで変更する値
	const int ALPHA_MAX         = 255; // 不透明度の最大値

	const int LIGHT_START_FRAME_COUNT  = 60;  // 光を描画し始めるフレーム数
	const int CHANGE_SCENE_FRAME_COUNT = 200; // シーン遷移を行うフレーム数

	const Size      LIGHT_SIZE(450, 110);                                 // 光のサイズ
	const Rect      LIGHT_RECT(Point(320, 240)-LIGHT_SIZE/2, LIGHT_SIZE); // 光の四角
	const RoundRect LIGHT_ROUNDRECT(LIGHT_RECT, 50);                      // 中心に表示し始める時間
	const double BLUR_RADIUS   = 50.0; // 影のぼかし方
	const double SHADOW_SPREAD = 15.0; // 影の広がり方

	const int    SMALL_LIGHT_NUM       = 12;   // 小さな光がなす角度
	const double SMALL_LIGHT_MOVE_RATE = 0.97; // 小さな光の移動の割合
	const double SMALL_LIGHT_DIST_MAX  = 300;  // 小さな光の最大移動距離
}


Robot::GameClearState::GameClearState()
	: _frameCount(0)
	, _backColor(Palette::MyBlack, 0)
	, _lightColor(Palette::MyWhite, 0)
{
	// 360度の全方向をリストに追加
	for (int i = 0; i < SMALL_LIGHT_NUM; ++i)
	{
		double radian = 2 * Pi*i / SMALL_LIGHT_NUM;
		_smallLightDirectionList.emplace_back(Cos(radian), Sin(radian));
	}
}


void Robot::GameClearState::update(GameManager & gameManager)
{
	++_frameCount;

	addAlpha(_backColor, BACK_ALPHA_SPEED);

	if (_frameCount < LIGHT_START_FRAME_COUNT) { return; }

	addAlpha(_lightColor, LIGHT_ALPHA_SPEED);

	_smallLightDist = SMALL_LIGHT_MOVE_RATE*_smallLightDist + (1 - SMALL_LIGHT_MOVE_RATE)*SMALL_LIGHT_DIST_MAX;

	if (_frameCount > CHANGE_SCENE_FRAME_COUNT)
	{
		gameManager.setSceneName(L"TitleScene", L"");
	}
}


void Robot::GameClearState::draw(const GameManager & gameManager) const
{
	gameManager.drawObjectAndLight();

	Window::ClientRect().draw(_backColor);

	if (_frameCount < LIGHT_START_FRAME_COUNT) { return; }

	LIGHT_ROUNDRECT.drawShadow(Vec2::Zero, BLUR_RADIUS, SHADOW_SPREAD, _lightColor);

	for (const auto & d : _smallLightDirectionList)
	{
		Circle(Window::Center() + d*_smallLightDist).drawShadow(Vec2::Zero, BLUR_RADIUS, SHADOW_SPREAD, _lightColor);
	}

	TextureAsset(L"Success").drawAt(Window::Center());
}


void Robot::GameClearState::addAlpha(Color & color, int addValue)
{
	if (color.a + addValue > ALPHA_MAX)
	{
		color.a = ALPHA_MAX;
		return;
	}

	color.a += addValue;
}
