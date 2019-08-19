#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	PoliceEnemy�N���X
	PatrolTeamEnemy�N���X�Ŏg�p����
	*/
	class PoliceEnemy : public EnemyBase
	{
	private:

		bool _isChasing; // �ǂ������Ă���Ƃ� true

		const Vec2 _startPos;  // ����

	public:

		PoliceEnemy(const Vec2 & pos);

		void drawLight() const override;

		/// <summary>
		/// ��������ύX����
		/// </summary>
		/// <param name="isChasing">
		/// true �Ȃ�v���C���[��ǂ������� , false �Ȃ玝��ɂ��ǂ�
		/// </param>
		void setChase(const bool isChasing)
		{
			_isChasing = isChasing;
		}

	private:

		Vec2 getMoveVec() override;

	};
}