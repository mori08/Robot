#include "DoctorDefence.h"


namespace
{
	const double SPEED = 1.2; // ����

	const double CHASE_DISTANCE_PIXEL = 100; // �v���C���[�ƃS�[���̋���(�s�N�Z��)������ȉ� -> �v���C���[��ǐ�
	const int    CHASE_DISTANCE_CELL  = 5;   // �v���C���[�ƃS�[���̓��̂�(���}�X)������ȉ� -> �v���C���[��ǐ�
}


Robot::DoctorDefence::DoctorDefence(const Vec2 & pos)
	: EnemyBase(pos)
	, _defencePos(pos)
{
}


void Robot::DoctorDefence::setDefencePos(const Vec2 & pos)
{
	_defencePos = pos;
}


Vec2 Robot::DoctorDefence::getMoveVec(GameManager & gameManager)
{
	const Vec2 playerPos = gameManager.getPlayerPos();
	const Vec2 goalPos   = gameManager.getGoalPos();

	if ((playerPos - goalPos).length() < CHASE_DISTANCE_PIXEL
		&& gameManager.getDistance(playerPos, goalPos) < CHASE_DISTANCE_PIXEL)
	{
		return SPEED*gameManager.getPath(_pos, gameManager.getPlayerPos());
	}

	return SPEED*gameManager.getPath(_pos, _defencePos);
}
