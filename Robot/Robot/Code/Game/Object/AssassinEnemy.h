#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	AssassinEnemy�N���X
	�v���C���[�ɋ߂��Ƒ����ɋ߂Â�
	���ɋ߂��ƒ�~����
	���̑��͂������v���C���[�ɋ߂Â�
	*/
	class AssassinEnemy : public EnemyBase
	{
	public:

		AssassinEnemy(const Vec2 & pos);

	private:

		Vec2 getMoveVec(GameManager & gameManager) override;

	};
}