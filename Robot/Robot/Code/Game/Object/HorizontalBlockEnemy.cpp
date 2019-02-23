#include "HorizontalBlockEnemy.h"


namespace
{
	const double SPEED = 0.6;
}


Robot::HorizontalBlockEnemy::HorizontalBlockEnemy(const Vec2 & pos)
	: EnemyBase(pos)
{
	
}


Vec2 Robot::HorizontalBlockEnemy::getMoveVec(GameManager & gameManager)
{
	return SPEED*gameManager.getPath(_pos, Vec2(gameManager.getPlayerPos().x, 240));
}
