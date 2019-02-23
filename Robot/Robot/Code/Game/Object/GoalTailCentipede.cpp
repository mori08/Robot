#include "GoalTailCentipede.h"
#include "CentipedeGoalBody.h"


namespace
{
	const size_t BODY_NUM = 10;
	const double MIN_DISTANCE = 10.0;
}


Robot::GoalTailCentipede::GoalTailCentipede(const Vec2 & pos)
	: CentipedeEnemy(pos)
	, _goalPos(pos)
	, _topOrBottom(true)
{
	for (size_t i = 0; i < BODY_NUM; ++i)
	{
		_bodyList.emplace_back(std::make_unique<CentipedeBody>(pos));
	}
	_bodyList.emplace_back(std::make_unique<CentipedeGoalBody>(pos));
}


Vec2 Robot::GoalTailCentipede::getGoalPos()
{
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
