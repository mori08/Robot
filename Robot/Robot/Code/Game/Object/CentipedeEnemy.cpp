#include "CentipedeEnemy.h"


namespace
{
	const size_t LEADER_INDEX = 0; // 先頭のインデックス
}


void Robot::CentipedeEnemy::update(GameManager & gameManager)
{
	_bodyList[LEADER_INDEX]->setGoalPos(getGoalPos());
	for (int i = 1; i < _bodyList.size(); ++i)
	{
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
