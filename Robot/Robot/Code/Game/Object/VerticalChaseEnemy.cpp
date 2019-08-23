#include "VerticalChaseEnemy.h"


namespace
{
	const double SPEED = 0.6;
	const double DISTANCE = 80.0;
}


Robot::VerticalChaseEnemy::VerticalChaseEnemy(const Vec2 & pos)
	: EnemyBase(pos)
{

}


Vec2 Robot::VerticalChaseEnemy::getMoveVec()
{
	const Vec2 player = GameManager::Instance().getPlayerPos();

	if (Abs(player.x - 320) < DISTANCE && (player - _pos).length() < DISTANCE)
	{
		return SPEED*GameManager::Instance().getPath(_pos, player);
	}

	// プレイヤーのx座標を追跡
	return SPEED*GameManager::Instance().getPath(_pos, Vec2(320, player.y));
}
