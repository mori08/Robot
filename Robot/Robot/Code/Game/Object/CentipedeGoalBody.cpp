#include "CentipedeGoalBody.h"
#include "../State/GameClearState.h"


namespace
{
	const int    CHANGE_TEXTURE_SPAN = 10; // �摜��ύX����t���[����
	const Size   TEXTURE_SIZE(40, 40);     // �摜�̃T�C�Y
	const double SPEED = 0.4;
	const double CLEAR_DISTANCE = 5.0; // �N���A���肪�s���鋗��
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
