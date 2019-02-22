#include "AssassinEnemy.h"


namespace
{
	const double FAST_SPEED = 0.75;
	const double SLOW_SPEED = 0.2;
	const double LIGHT_RADIUS = 100;
}


Robot::AssassinEnemy::AssassinEnemy(const Vec2 & pos)
	: EnemyBase(pos)
{
}


Vec2 Robot::AssassinEnemy::getMoveVec(GameManager & gameManager)
{
	if ((_pos - gameManager.getPlayerPos()).length() < LIGHT_RADIUS)
	{
		return FAST_SPEED*gameManager.getPath(_pos, gameManager.getPlayerPos());
	}

	if ((_pos - gameManager.getLightPos()).length() < LIGHT_RADIUS)
	{
		return Vec2::Zero;
	}

	return SLOW_SPEED*gameManager.getPath(_pos, gameManager.getPlayerPos());
}
