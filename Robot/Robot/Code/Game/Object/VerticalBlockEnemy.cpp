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
	// �v���C���[��x���W��ǐ�
	return SPEED*GameManager::Instance().getPath(_pos, Vec2(320, GameManager::Instance().getPlayerPos().y));
}
