#include "RunAwayGoal.h"


namespace
{
	const double PLAYER_MIN_DISTANCE = 12.0;
	const int RUN_POINT_NUM = 4;
	const double SPEED = 0.5;
}


Robot::RunAwayGoal::RunAwayGoal(const Vec2 & pos)
	: GameGoal(pos)
{
	_goalPointId = Random(0, 3);
	_runPointList.emplace_back(0, 0);
	_runPointList.emplace_back(StageData::WIDTH - 1, 0);
	_runPointList.emplace_back(StageData::WIDTH - 1, StageData::HEIGHT - 1);
	_runPointList.emplace_back(0, StageData::HEIGHT - 1);

	_pos = StageData::centerPosOfCell(_runPointList[_goalPointId]);
}


Vec2 Robot::RunAwayGoal::getMoveVec(GameManager & gameManager)
{
	if (_runPointList[_goalPointId] != StageData::translatePos(_pos))
	{
		return SPEED*gameManager.getPath(_pos,StageData::centerPosOfCell(_runPointList[_goalPointId]));
	}
	
	int nextId = RandomSelect<int>({ -1,1 });
	_goalPointId = (_goalPointId + nextId + RUN_POINT_NUM) % RUN_POINT_NUM;
	return Vec2::Zero;
}
