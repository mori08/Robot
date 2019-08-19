#include "ChaseEnemy.h"


namespace
{
	const double SPEED = 0.8;
}


Robot::ChaseEnemy::ChaseEnemy(const Vec2 & pos)
	: EnemyBase(pos)
{

}


Vec2 Robot::ChaseEnemy::getMoveVec()
{
	// �v���C���[��ǐ�
	return SPEED*GameManager::Instance().getPath(_pos, GameManager::Instance().getPlayerPos());
}
