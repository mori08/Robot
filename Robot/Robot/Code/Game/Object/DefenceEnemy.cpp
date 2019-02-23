#include "DefenceEnemy.h"


namespace
{
	const double SPEED = 0.8;
	const double RATE = 0.5; // プレイヤーとゴールの内分点の比
}


Robot::DefenceEnemy::DefenceEnemy(const Vec2 & pos)
	: EnemyBase(pos)
{

}


Vec2 Robot::DefenceEnemy::getMoveVec(GameManager & gameManager)
{
	Vec2 goalPos = (1-RATE)*gameManager.getPlayerPos() + RATE*gameManager.getGoalPos();
	if (gameManager.isWalkingAblePos(goalPos))
	{
		return SPEED*gameManager.getPath(_pos, goalPos);
	}
	return SPEED*gameManager.getPath(_pos, gameManager.getGoalPos());
}
