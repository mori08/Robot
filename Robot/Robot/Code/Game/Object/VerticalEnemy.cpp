#include "VerticalEnemy.h"


Robot::VerticalEnemy::VerticalEnemy(const Vec2 & pos)
	: EnemyBase(pos)
	, _moveVec(Vec2::Down)
{

}


Vec2 Robot::VerticalEnemy::getMoveVec(GameManager & gameManager)
{
	if (gameManager.isWalkingAblePos(_pos + _moveVec))
	{
		return _moveVec;
	}
	_moveVec *= -1; // •ûŒü“]Š·
	return Vec2::Zero;
}
