#include "CentipedeGoalBody.h"


namespace
{
	const int    CHANGE_TEXTURE_SPAN = 10; // �摜��ύX����t���[����
	const Size   TEXTURE_SIZE(40, 40);     // �摜�̃T�C�Y
}


Robot::CentipedeGoalBody::CentipedeGoalBody(const Vec2 & pos)
	: CentipedeBody(pos)
{
}


void Robot::CentipedeGoalBody::draw() const
{
	const Point texturePos(_frameCount / CHANGE_TEXTURE_SPAN, 0);
	TextureAsset(L"Goal")(texturePos*TEXTURE_SIZE, TEXTURE_SIZE).drawAt(_pos);
}


void Robot::CentipedeGoalBody::connectedPlayerProcess(GameManager & gameManager)
{
	gameManager.gameClear();
}
