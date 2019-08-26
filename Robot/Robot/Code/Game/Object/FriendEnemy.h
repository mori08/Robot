#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	FriendEnemy�N���X
	�X�e�[�W�����S�ɏƂ炷
	�X�e�[�W��h�炷
	�������X�s�[�h���グ��
	*/
	class FriendEnemy : public EnemyBase
	{
	private:

		double _speed;      // ����

		int    _shake;      // ��ʂ̗h��̑傫��

	public:

		FriendEnemy(const Vec2 & pos);

	private:

		void drawLight() const override;

		Vec2 getMoveVec() override;

		void gameOver() override;

	};
}