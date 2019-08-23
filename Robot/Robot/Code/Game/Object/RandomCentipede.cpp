#include "RandomCentipede.h"


namespace
{
	const size_t BODY_NUM = 8;
	const double MIN_DISTANCE = 10.0;
}


Robot::RandomCentipede::RandomCentipede(const Vec2 & pos)
	: CentipedeEnemy(pos)
	, _goalPos(pos)
{
	for (size_t i = 0; i < BODY_NUM; ++i)
	{
		_bodyList.emplace_back(std::make_unique<CentipedeBody>(pos));
	}
}

Vec2 Robot::RandomCentipede::getGoalPos()
{
	// ƒ‰ƒ“ƒ_ƒ€‚ÈÀ•W‚ÖˆÚ“®
	if ((_goalPos - _bodyList[0]->getPos()).length() < MIN_DISTANCE || !GameManager::Instance().isWalkingAblePos(_goalPos))
	{
		_goalPos.x = Random(640.0);
		_goalPos.y = _topOrBottom ? 20 : 460;
		if (GameManager::Instance().isWalkingAblePos(_goalPos))
		{
			_topOrBottom = !_topOrBottom;
		}
	}
	return _goalPos;
}
