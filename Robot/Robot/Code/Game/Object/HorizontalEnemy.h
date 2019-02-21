#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	HorizontalEnemy�N���X
	�����ړ�����G
	*/
	class HorizontalEnemy : public EnemyBase
	{
	private:

		Vec2 _moveVec; // �ړ��x�N�g��

	public:

		/// <summary>
		/// �����ړ�����G
		/// </summary>
		/// <param name="pos"> �������W </param>
		HorizontalEnemy(const Vec2 & pos);

	private:

		Vec2 getMoveVec(GameManager & gameManager) override;

	};
}