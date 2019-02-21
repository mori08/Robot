#include "HorizontalEnemy.h"


Robot::HorizontalEnemy::HorizontalEnemy(const Vec2 & pos)
	: EnemyBase(pos)
	, _moveVec(Vec2::Right)
{

}

Vec2 Robot::HorizontalEnemy::getMoveVec(GameManager & gameManager)
{
	if (gameManager.isWalkingAblePos(_pos + _moveVec))
	{
		return _moveVec;
	}
	_moveVec *= -1; // •ûŒü“]Š·
	return Vec2::Zero;
}
