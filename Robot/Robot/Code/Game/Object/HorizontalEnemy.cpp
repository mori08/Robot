#include "HorizontalEnemy.h"


namespace
{
	const double SPEED = 0.8;
}


Robot::HorizontalEnemy::HorizontalEnemy(const Vec2 & pos)
	: EnemyBase(pos)
	, _moveVec(SPEED*Vec2::Right)
{

}

Vec2 Robot::HorizontalEnemy::getMoveVec()
{
	// xÀ•W•ûŒü‚É‰•œ‚·‚é
	if (GameManager::Instance().isWalkingAblePos(_pos + _moveVec))
	{
		return _moveVec;
	}
	_moveVec *= -1; // •ûŒü“]Š·
	return Vec2::Zero;
}
