#include "RandomCentipede.h"


namespace
{
	const size_t BODY_NUM = 15;
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
	if ((_goalPos - _bodyList[0]->getPos()).length() < MIN_DISTANCE || !GameManager::Instance().isWalkingAblePos(_goalPos))
	{
		_goalPos.x = RandomSelect<double>({ 20,620 });
		_goalPos.y = Random(480.0);
	}
	return _goalPos;
}
