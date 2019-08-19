#include "AssassinEnemy.h"


namespace
{
	const double FAST_SPEED = 0.75;
	const double SLOW_SPEED = 0.2;
	const double LIGHT_RADIUS = 100;
}


Robot::AssassinEnemy::AssassinEnemy(const Vec2 & pos)
	: EnemyBase(pos)
{
}


Vec2 Robot::AssassinEnemy::getMoveVec()
{
	// �v���C���[�Ƌ߂��Ƃ��v���C���[��ǐ�
	if ((_pos - GameManager::Instance().getPlayerPos()).length() < LIGHT_RADIUS)
	{
		return FAST_SPEED*GameManager::Instance().getPath(_pos, GameManager::Instance().getPlayerPos());
	}

	// �����߂��Ƃ��Î~
	if ((_pos - GameManager::Instance().getLightPos()).length() < LIGHT_RADIUS)
	{
		return Vec2::Zero;
	}

	// �������v���C���[��ǐ�
	return SLOW_SPEED*GameManager::Instance().getPath(_pos, GameManager::Instance().getPlayerPos());
}
