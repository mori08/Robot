#include "DefenceEnemy.h"


namespace
{
	const double SPEED = 0.4;
	const int    CHANGE_MOTION_SPAN = 60;
}


Robot::DefenceEnemy::DefenceEnemy(const Vec2 & pos)
	: EnemyBase(pos)
	, _attackOrDefence(false)
{

}


Vec2 Robot::DefenceEnemy::getMoveVec(GameManager & gameManager)
{
	if (_frameCount%CHANGE_MOTION_SPAN == 0)
	{
		_attackOrDefence = !_attackOrDefence;
	}

	if (_attackOrDefence)
	{
		return SPEED*gameManager.getPath(_pos, gameManager.getPlayerPos());
	}
	else
	{
		return SPEED*gameManager.getPath(_pos, gameManager.getGoalPos());
	}
}
