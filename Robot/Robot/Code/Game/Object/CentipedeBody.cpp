#include "CentipedeBody.h"
#include "../State/GameOverState.h"


namespace
{
	const int  TEXTURE_CHANGE_SPAN = 4;    // 画像を変更する間隔のフレーム数
	const Size TEXTURE_SIZE(40, 40);       // 画像の大きさ
	const double GAMEOVER_DISTANCE = 15.0; // ゲームオーバー判定が行われる距離
	const double SPEED = 0.4;
}


Robot::CentipedeBody::CentipedeBody(const Vec2 & pos)
	: GameObject(pos)
	, _goalPos(pos)
	, _frameCount(0)
{
}


void Robot::CentipedeBody::update()
{
	++_frameCount;

	moveObject(SPEED*GameManager::Instance().getPath(_pos, _goalPos));

	if ((_pos - GameManager::Instance().getPlayerPos()).length() < GAMEOVER_DISTANCE)
	{
		connectedPlayerProcess();
	}
}


void Robot::CentipedeBody::draw() const
{
	Point texturePos = Point(_frameCount / TEXTURE_CHANGE_SPAN, 0);
	TextureAsset(L"Enemy")(texturePos*TEXTURE_SIZE, TEXTURE_SIZE).drawAt(_pos);
}


void Robot::CentipedeBody::connectedPlayerProcess()
{
	GameManager::Instance().changeGameState(std::make_unique<GameOverState>());
}
