#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	VerticalEnemy�N���X
	�����ړ�����G
	*/
	class VerticalEnemy : public EnemyBase
	{
	private:

		Vec2 _moveVec; // �ړ��x�N�g��

	public:

		/// <summary>
		/// �����ړ�����G
		/// </summary>
		/// <param name="pos"> �������W </param>
		VerticalEnemy(const Vec2 & pos);

	private:

		Vec2 getMoveVec() override;

	};
}