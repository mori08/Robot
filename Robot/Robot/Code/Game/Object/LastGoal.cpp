#include "LastGoal.h"


namespace
{
	const double CHANGE_DISTANCE = 1.0; // 目的地を変更する距離
	const double SPEED = 0.8;
}


Robot::LastGoal::LastGoal(const Vec2 & pos)
	: GameGoal(pos)
	, _goalPosIndex(1)
{
	_goalPosList.emplace_back(100, 20);
	_goalPosList.emplace_back(320, 20);
	_goalPosList.emplace_back(540, 20);
	_goalPosList.emplace_back(540, 240);
	_goalPosList.emplace_back(540, 460);
	_goalPosList.emplace_back(320, 460);
	_goalPosList.emplace_back(100, 460);
	_goalPosList.emplace_back(100, 240);
}


Vec2 Robot::LastGoal::getMoveVec()
{
	// プレイヤーから遠ざかるための点を選択し移動
	if ((_pos - _goalPosList[_goalPosIndex]).length() < CHANGE_DISTANCE)
	{
		double maxDistance = 0;
		int    maxIndex = _goalPosIndex;
		for (int i = -1; i <= 1; ++i)
		{
			int index = (_goalPosIndex + i + (int)_goalPosList.size()) % (int)_goalPosList.size();
			if ((GameManager::Instance().getPlayerPos() - _goalPosList[index]).length() > maxDistance)
			{
				maxDistance = (GameManager::Instance().getPlayerPos() - _goalPosList[index]).length();
				maxIndex    = index;
			}
		}
		_goalPosIndex = maxIndex;
	}

	return SPEED*GameManager::Instance().getPath(_pos, _goalPosList[_goalPosIndex]);
}
