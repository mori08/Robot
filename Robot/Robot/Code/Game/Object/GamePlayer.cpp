#include "GamePlayer.h"
#include "../../MyColor.h"


namespace
{
	const double BASE_VALUE = 1.0; // プレイヤーの方向を決めるための基準値
	const double ZERO_LINE = 0.01; // ベクトルの大きさを0とみなす基準値

	const double RADIUS = 10; // 半径
	const double BLUR   = 10; // ぼかし方
	const double SPREAD = 10; // 広がり方

	const Size TEXTURE_SIZE(40, 40);      // 画像サイズ
	const int  CHEANGE_TEXTURE_SPAN = 60; // 画像を変更する頻度

	const double CHANGE_RATE            = 0.95;  // _lightCircleRateを変更する割合
	const double RATE_MIN               = 0.001; // _lightCircleRateの最小値
	const double LIGHT_CIRCLE_RADIUS    = 40;    // 光の輪の半径
	const double LIGHT_CIRCLE_THICKNESS = 1;     // 光の輪の厚さ

	const double SPEED = 1.2;
}


Robot::GamePlayer::GamePlayer(const Vec2 & pos)
	: GameObject(pos)
{
}


void Robot::GamePlayer::update()
{
	_lightCircleRate *= CHANGE_RATE;
	if (_lightCircleRate < RATE_MIN) { _lightCircleRate = 1; }

	moveObject(getMoveVec());

	GameManager::Instance().setPlayerPos(_pos);
}


void Robot::GamePlayer::draw() const
{
	TextureAsset(L"Player").drawAt(_pos);
}


void Robot::GamePlayer::drawLight() const
{
	ColorF lightColor(Palette::MyWhite);
	lightColor.setAlpha(Sqrt(_lightCircleRate));
	Circle(_pos, (1 - _lightCircleRate)*LIGHT_CIRCLE_RADIUS).drawFrame(LIGHT_CIRCLE_THICKNESS, LIGHT_CIRCLE_THICKNESS, lightColor);
}


Vec2 Robot::GamePlayer::getMoveVec() const
{
	Vec2 moveVec = Vec2::Zero;

	if (Input::KeyA.pressed)
	{
		moveVec.x -= BASE_VALUE;
	}

	if (Input::KeyD.pressed)
	{
		moveVec.x += BASE_VALUE;
	}

	if (Input::KeyW.pressed)
	{
		moveVec.y -= BASE_VALUE;
	}

	if (Input::KeyS.pressed)
	{
		moveVec.y += BASE_VALUE;
	}
	
	return (moveVec.length() < ZERO_LINE) ? Vec2::Zero : SPEED*moveVec.normalize();
}
