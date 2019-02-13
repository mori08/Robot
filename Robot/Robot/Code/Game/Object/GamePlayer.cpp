#include "GamePlayer.h"


namespace
{
	const double BASE_VALUE = 1.0; // プレイヤーの方向を決めるための基準値
	const double ZERO_LINE = 0.01; // ベクトルの大きさを0とみなす基準値

	const double RADIUS = 10; // 半径
	const double BLUR   = 10; // ぼかし方
	const double SPREAD = 10; // 広がり方

	const Size TEXTURE_SIZE(40, 40);      // 画像サイズ
	const int  CHEANGE_TEXTURE_SPAN = 60; // 画像を変更する頻度
}


Robot::GamePlayer::GamePlayer(const Vec2 & pos)
	: GameObject(pos)
	, _texturePos(0,0)
	, _frameCount(0)
{
}


void Robot::GamePlayer::update(GameManager & gameManager)
{
	++_frameCount;

	if (_frameCount%CHEANGE_TEXTURE_SPAN == 0)
	{
		_texturePos.x++;
	}

	moveObject(gameManager, getMoveVec());

	gameManager.setPlayerPos(_pos)
}


void Robot::GamePlayer::draw() const
{
	TextureAsset(L"Player")(_texturePos*TEXTURE_SIZE, TEXTURE_SIZE).drawAt(_pos);
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
	
	return (moveVec.length() < ZERO_LINE) ? Vec2::Zero : moveVec.normalize();
}
