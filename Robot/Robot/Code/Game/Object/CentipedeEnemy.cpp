#include "CentipedeEnemy.h"


namespace
{
	const size_t LEADER_INDEX  = 0;  // 先頭のインデックス
	const size_t BODY_DISTANCE = 30; // 体の部品が保つ距離
}


void Robot::CentipedeEnemy::update(GameManager & gameManager)
{
	_bodyList[LEADER_INDEX]->setGoalPos(getGoalPos());
	for (int i = 1; i < _bodyList.size(); ++i)
	{
		if ((_bodyList[i]->getPos() - _bodyList[i-1]->getPos()).length() < BODY_DISTANCE)
		{
			continue;
		}
		_bodyList[i]->setGoalPos(_bodyList[i - 1]->getPos());
	}

	for (auto && body : _bodyList)
	{
		body->update(gameManager);
	}
}


void Robot::CentipedeEnemy::draw() const
{
	for (const auto & body : _bodyList)
	{
		body->draw();
	}
}
