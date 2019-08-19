#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	HorizontalBlockEnemy�N���X
	�v���C���[��x���W��ǐՂ���
	*/
	class HorizontalBlockEnemy : public EnemyBase
	{
	public:

		/// <summary>
		/// �v���C���[��x���W��ǐՂ���G
		/// </summary>
		/// <param name="pos"> �������W </param>
		HorizontalBlockEnemy(const Vec2 & pos);

	private:

		Vec2 getMoveVec() override;

	};
}