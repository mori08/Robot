#include "ChasePlayerCentipede.h"


namespace
{
	const size_t BODY_NUM = 15;
}


Robot::ChasePlayerCentipede::ChasePlayerCentipede(const Vec2 & pos)
	: CentipedeEnemy(pos)
{
	for (size_t i = 0; i < BODY_NUM; ++i)
	{
		_bodyList.emplace_back(std::make_unique<CentipedeBody>(pos));
	}
}

Vec2 Robot::ChasePlayerCentipede::getGoalPos()
{
	return GameManager::Instance().getPlayerPos();
}
