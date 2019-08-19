#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	DefenceEnemy�N���X
	�S�[�������G
	*/
	class DefenceEnemy : public EnemyBase
	{
	public:

		/// <summary>
		/// �S�[�������G
		/// </summary>
		/// <param name="pos"> �������W </param>
		DefenceEnemy(const Vec2 & pos);

	private:

		Vec2 getMoveVec() override;

	};
}