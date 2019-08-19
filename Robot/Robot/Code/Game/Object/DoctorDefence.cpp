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


Vec2 Robot::DoctorDefence::getMoveVec()
{
	const Vec2 playerPos = GameManager::Instance().getPlayerPos();
	const Vec2 goalPos   = GameManager::Instance().getGoalPos();

	// プレイヤーが近いとき プレイヤーを追跡
	if ((playerPos - goalPos).length() < CHASE_DISTANCE_PIXEL
		&& GameManager::Instance().getDistance(playerPos, goalPos) < CHASE_DISTANCE_CELL)
	{
		return SPEED*GameManager::Instance().getPath(_pos, playerPos);
	}

	// DoctorEnemyに指定された場所へ移動
	return SPEED*GameManager::Instance().getPath(_pos, _defencePos);
}
