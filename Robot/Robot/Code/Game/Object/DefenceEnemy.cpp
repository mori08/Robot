#include "DefenceEnemy.h"


namespace
{
	const double SPEED = 0.8;
	const double RATE = 0.5; // �v���C���[�ƃS�[���̓����_�̔�
}


Robot::DefenceEnemy::DefenceEnemy(const Vec2 & pos)
	: EnemyBase(pos)
{

}


Vec2 Robot::DefenceEnemy::getMoveVec()
{
	// �v���C���[�ƃS�[���̓����_�ֈړ�
	Vec2 goalPos = (1-RATE)*GameManager::Instance().getPlayerPos() + RATE*GameManager::Instance().getGoalPos();

	// �ړ��ł��Ȃ��ꍇ�S�[���ֈړ�
	if (GameManager::Instance().isWalkingAblePos(goalPos))
	{
		return SPEED*GameManager::Instance().getPath(_pos, goalPos);
	}

	return SPEED*GameManager::Instance().getPath(_pos, GameManager::Instance().getGoalPos());
}
