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
	private:

		bool _attackOrDefence; // true�̂Ƃ��v���C���[��ǂ����� , false�̂Ƃ��S�[����ǂ�������

	public:

		/// <summary>
		/// �S�[�������G
		/// </summary>
		/// <param name="pos"> �������W </param>
		DefenceEnemy(const Vec2 & pos);

	private:

		Vec2 getMoveVec(GameManager & gameManager) override;

	};
}