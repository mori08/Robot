#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	ChaseEnemy�N���X
	�v���C���[��ǐՂ���G
	*/
	class ChaseEnemy : public EnemyBase
	{
	public:

		/// <summary>
		/// �v���C���[��ǐՂ���G
		/// </summary>
		/// <param name="pos"> �������W </param>
		ChaseEnemy(const Vec2 & pos);

	private:

		Vec2 getMoveVec(GameManager & gameManager) override;

	};
}