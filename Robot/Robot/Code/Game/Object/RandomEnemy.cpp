#include "RandomEnemy.h"


namespace
{
	const double SPEED = 0.8;
	const double MIN_VEC_LENGTH = 0.5;
}


Robot::RandomEnemy::RandomEnemy(const Vec2 & pos)
	: EnemyBase(pos)
	, _goalPos(pos)
{
}


Vec2 Robot::RandomEnemy::getMoveVec()
{
	// ƒ‰ƒ“ƒ_ƒ€‚ÈÀ•W‚ÖˆÚ“®
	Vec2 moveVec = GameManager::Instance().getPath(_pos, _goalPos);
	if (moveVec.length() < MIN_VEC_LENGTH)
	{
		_goalPos = RandomVec2(StageData::SIZE*StageData::WIDTH, StageData::SIZE*StageData::HEIGHT);
		return Vec2::Zero;
	}
	return SPEED*moveVec;
}
