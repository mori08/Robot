#include "HorizontalChaseEnemy.h"


namespace
{
	const double SPEED    = 0.6;
	const double DISTANCE = 80.0;
}


Robot::HorizontalChaseEnemy::HorizontalChaseEnemy(const Vec2 & pos)
	: EnemyBase(pos)
{

}


Vec2 Robot::HorizontalChaseEnemy::getMoveVec()
{
	const Vec2 player = GameManager::Instance().getPlayerPos();

	if (Abs(player.y - 240) < DISTANCE && (player - _pos).length() < DISTANCE)
	{
		return SPEED*GameManager::Instance().getPath(_pos, player);
	}

	// プレイヤーのx座標を追跡
	return SPEED*GameManager::Instance().getPath(_pos, Vec2(player.x, 240));
}
