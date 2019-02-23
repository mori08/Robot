#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	VerticalBlockEnemy�N���X
	�v���C���[��y���W��ǐՂ���
	*/
	class VerticalBlockEnemy : public EnemyBase
	{
	public:

		/// <summary>
		/// �v���C���[��x���W��ǐՂ���G
		/// </summary>
		/// <param name="pos"> �������W </param>
		VerticalBlockEnemy(const Vec2 & pos);

	private:

		Vec2 getMoveVec(GameManager & gameManager) override;

	};
}
