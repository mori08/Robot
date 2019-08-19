#include "VerticalBlockEnemy.h"


namespace
{
	const double SPEED = 0.6;
}


Robot::VerticalBlockEnemy::VerticalBlockEnemy(const Vec2 & pos)
	: EnemyBase(pos)
{

}


Vec2 Robot::VerticalBlockEnemy::getMoveVec()
{
	// プレイヤーのx座標を追跡
	return SPEED*GameManager::Instance().getPath(_pos, Vec2(320, GameManager::Instance().getPlayerPos().y));
}
