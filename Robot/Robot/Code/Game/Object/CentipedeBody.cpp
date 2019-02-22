#include "CentipedeBody.h"


namespace
{
	const int  TEXTURE_CHANGE_SPAN = 4;    // 画像を変更する間隔のフレーム数
	const Size TEXTURE_SIZE(40, 40);       // 画像の大きさ
	const double GAMEOVER_DISTANCE = 15.0; // ゲームオーバー判定が行われる距離
	const double SPEED = 0.6;
}


Robot::CentipedeBody::CentipedeBody(const Vec2 & pos)
	: GameObject(pos)
	, _goalPos(pos)
{
}


void Robot::CentipedeBody::update(GameManager & gameManager)
{
	++_frameCount;

	moveObject(gameManager, SPEED*gameManager.getPath(_pos, _goalPos));

	if ((_pos - gameManager.getPlayerPos()).length() < GAMEOVER_DISTANCE)
	{
		connectedPlayerProcess(gameManager);
	}
}


void Robot::CentipedeBody::draw() const
{
	const Point texturePos = TEXTURE_SIZE*Point(_frameCount / TEXTURE_CHANGE_SPAN, 0);
	TextureAsset(L"Enemy")(texturePos*TEXTURE_SIZE, TEXTURE_SIZE).drawAt(_pos);
}


void Robot::CentipedeBody::connectedPlayerProcess(GameManager & gameManager)
{
	gameManager.gameOver();
}
