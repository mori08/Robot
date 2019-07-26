#include "DoctorDefence.h"


namespace
{
	const double SPEED = 1.2; // 速さ

	const double CHASE_DISTANCE_PIXEL = 100; // プレイヤーとゴールの距離(ピクセル)がこれ以下 -> プレイヤーを追跡
	const int    CHASE_DISTANCE_CELL  = 5;   // プレイヤーとゴールの道のり(何マス)がこれ以下 -> プレイヤーを追跡
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
