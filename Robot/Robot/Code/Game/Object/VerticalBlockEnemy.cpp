#include "VerticalBlockEnemy.h"


namespace
{
	const double SPEED = 0.6;
}


Robot::VerticalBlockEnemy::VerticalBlockEnemy(const Vec2 & pos)
	: EnemyBase(pos)
{

}


Vec2 Robot::VerticalBlockEnemy::getMoveVec(GameManager & gameManager)
{
	return SPEED*gameManager.getPath(_pos, Vec2(320,gameManager.getPlayerPos().y));
}
