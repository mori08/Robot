#include "LockKey.h"


namespace
{
	const double SPEED = 0.1;
	const double MIN_VEC_LENGTH = 0.05;
}


Robot::LockKey::LockKey(const Vec2 & pos)
	: DoctorSwitch(pos)
{
	_goal = pos;
}


Vec2 Robot::LockKey::getMoveVec(GameManager & gameManager)
{
	if (_isPressed) { return Vec2::Zero; }

	Vec2 moveVec = gameManager.getPath(_pos, _goal);
	if (moveVec.length() < MIN_VEC_LENGTH)
	{
		_goal = RandomVec2(StageData::SIZE*StageData::WIDTH, StageData::SIZE*StageData::HEIGHT);
		return Vec2::Zero;
	}

	return SPEED*moveVec;
}
