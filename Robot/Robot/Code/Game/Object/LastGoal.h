#pragma once


#include "GameGoal.h"


namespace Robot
{
	/*
	LastGoal�N���X
	�ŏI�X�e�[�W(9�Ԗ�)�Ɏg�p����S�[��
	�X�e�[�W��4�p�̂��v���C���[���牓���ꏊ���v�Z����
	*/
	class LastGoal : public GameGoal
	{
	private:

		int _goalPosIndex;              // ���������Ă���ړI�n�̔ԍ�
		std::vector<Vec2> _goalPosList; // �l�p

	public:

		LastGoal(const Vec2 & pos);

	private:

		Vec2 getMoveVec(GameManager & gameManager) override;

	};
}