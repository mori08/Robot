#include "HorizontalBlockEnemy.h"


namespace
{
	const double SPEED = 0.6;
}


Robot::HorizontalBlockEnemy::HorizontalBlockEnemy(const Vec2 & pos)
	: EnemyBase(pos)
{
	
}


Vec2 Robot::HorizontalBlockEnemy::getMoveVec()
{
	// �v���C���[��x���W��ǐ�
	return SPEED*GameManager::Instance().getPath(_pos, Vec2(GameManager::Instance().getPlayerPos().x, 240));
}
