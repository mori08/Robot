#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	RandomEnemy�N���X
	�����_���ɍ��W��ݒ肵�Ĉړ�����G
	*/
	class RandomEnemy : public EnemyBase
	{
	private:

		Vec2 _goalPos; // �ړI���W

	public:

		/// <summary>
		/// �����_���ɍ��W��ݒ肵�Ĉړ�����G
		/// </summary>
		/// <param name="pos"> �������W </param>
		RandomEnemy(const Vec2 & pos);

	private:

		Vec2 getMoveVec() override;

	};
}