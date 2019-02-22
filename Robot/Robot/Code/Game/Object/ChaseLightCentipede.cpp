#include "ChaseLightCentipede.h"


namespace
{
	const size_t BODY_NUM = 15;
}


Robot::ChaseLightCentipede::ChaseLightCentipede(const Vec2 & pos)
	: CentipedeEnemy(pos)
{
	for (size_t i = 0; i < BODY_NUM; ++i)
	{
		_bodyList.emplace_back(std::make_unique<CentipedeBody>(pos));
	}
}

Vec2 Robot::ChaseLightCentipede::getGoalPos()
{
	return GameManager::Instance().getLightPos();
}
