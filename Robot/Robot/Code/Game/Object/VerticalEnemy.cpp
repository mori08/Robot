#include "VerticalEnemy.h"


namespace
{
	const double SPEED = 0.8;
}


Robot::VerticalEnemy::VerticalEnemy(const Vec2 & pos)
	: EnemyBase(pos)
	, _moveVec(SPEED*Vec2::Down)
{

}


Vec2 Robot::VerticalEnemy::getMoveVec()
{
	// yÀ•W•ûŒü‚É‰•œ‚·‚é
	if (GameManager::Instance().isWalkingAblePos(_pos + _moveVec))
	{
		return _moveVec;
	}
	_moveVec *= -1; // •ûŒü“]Š·
	return Vec2::Zero;
}
