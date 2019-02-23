#include "CentipedeEnemy.h"


namespace
{
	const size_t LEADER_INDEX  = 0;  // �擪�̃C���f�b�N�X
	const size_t BODY_DISTANCE = 40; // �̂̕��i���ۂ���
}


void Robot::CentipedeEnemy::update(GameManager & gameManager)
{
	if (gameManager.isWalkingAblePos(getGoalPos()))
	{
		_bodyList[LEADER_INDEX]->setGoalPos(getGoalPos());
	}

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
