#include "DefenceCentipede.h"


namespace
{
	const size_t BODY_NUM = 10;
	const double RANGE    = 100.0;
	const double MIN_DISTANCE = 10.0;
}


Robot::DefenceCentipede::DefenceCentipede(const Vec2 & pos)
	: CentipedeEnemy(pos)
	, _goalPos(pos)
{
	for (size_t i = 0; i < BODY_NUM; ++i)
	{
		_bodyList.emplace_back(std::make_unique<CentipedeBody>(pos));
	}
}

Vec2 Robot::DefenceCentipede::getGoalPos()
{
	// ƒ‰ƒ“ƒ_ƒ€‚ÈÀ•W‚ÖˆÚ“®
	if ((_goalPos - _bodyList[0]->getPos()).length() < MIN_DISTANCE || !GameManager::Instance().isWalkingAblePos(_goalPos))
	{
		_goalPos = GameManager::Instance().getGoalPos() + RandomVec2(Circle(Vec2::Zero, RANGE));
	}
	return _goalPos;
}
