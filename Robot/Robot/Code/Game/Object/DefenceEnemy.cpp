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


Vec2 Robot::DefenceEnemy::getMoveVec()
{
	// プレイヤーとゴールの内分点へ移動
	Vec2 goalPos = (1-RATE)*GameManager::Instance().getPlayerPos() + RATE*GameManager::Instance().getGoalPos();

	// 移動できない場合ゴールへ移動
	if (GameManager::Instance().isWalkingAblePos(goalPos))
	{
		return SPEED*GameManager::Instance().getPath(_pos, goalPos);
	}

	return SPEED*GameManager::Instance().getPath(_pos, GameManager::Instance().getGoalPos());
}
