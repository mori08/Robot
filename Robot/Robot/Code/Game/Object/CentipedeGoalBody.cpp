#include "CentipedeGoalBody.h"
#include "../State/GameClearState.h"


namespace
{
	const int    CHANGE_TEXTURE_SPAN = 10; // 画像を変更するフレーム数
	const Size   TEXTURE_SIZE(40, 40);     // 画像のサイズ
	const double SPEED = 0.4;
	const double CLEAR_DISTANCE = 5.0; // クリア判定が行われる距離
}


Robot::CentipedeGoalBody::CentipedeGoalBody(const Vec2 & pos)
	: CentipedeBody(pos)
{
}


void Robot::CentipedeGoalBody::update()
{
	++_frameCount;

	moveObject(SPEED*GameManager::Instance().getPath(_pos, _goalPos));

	GameManager::Instance().setGoalPos(_pos);

	if ((_pos - GameManager::Instance().getPlayerPos()).length() < CLEAR_DISTANCE)
	{
		connectedPlayerProcess();
	}
}


void Robot::CentipedeGoalBody::draw() const
{
	const Point texturePos(_frameCount / CHANGE_TEXTURE_SPAN, 0);
	TextureAsset(L"Goal")(texturePos*TEXTURE_SIZE, TEXTURE_SIZE).drawAt(_pos);
}


void Robot::CentipedeGoalBody::connectedPlayerProcess()
{
	GameManager::Instance().changeGameState(std::make_unique<GameClearState>());
}
