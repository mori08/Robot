#include "CentipedeBody.h"


namespace
{
	const int  TEXTURE_CHANGE_SPAN = 4;    // �摜��ύX����Ԋu�̃t���[����
	const Size TEXTURE_SIZE(40, 40);       // �摜�̑傫��
	const double GAMEOVER_DISTANCE = 15.0; // �Q�[���I�[�o�[���肪�s���鋗��
	const double SPEED = 0.5;
}


Robot::CentipedeBody::CentipedeBody(const Vec2 & pos)
	: GameObject(pos)
	, _goalPos(pos)
	, _frameCount(0)
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
	Point texturePos = Point(_frameCount / TEXTURE_CHANGE_SPAN, 0);
	TextureAsset(L"Enemy")(texturePos*TEXTURE_SIZE, TEXTURE_SIZE).drawAt(_pos);
}


void Robot::CentipedeBody::connectedPlayerProcess(GameManager & gameManager)
{
	gameManager.gameOver();
}
