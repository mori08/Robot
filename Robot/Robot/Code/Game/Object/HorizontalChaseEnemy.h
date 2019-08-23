#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	HorizontalEnemy�N���X
	�����ړ�����G
	*/
	class HorizontalChaseEnemy : public EnemyBase
	{
	private:

		Vec2 _moveVec; // �ړ��x�N�g��

	public:

		/// <summary>
		/// �����ړ�����G
		/// </summary>
		/// <param name="pos"> �������W </param>
		HorizontalChaseEnemy(const Vec2 & pos);

	private:

		Vec2 getMoveVec() override;

	};
}