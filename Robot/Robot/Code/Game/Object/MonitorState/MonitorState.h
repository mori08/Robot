#pragma once


#include <Siv3D.hpp>


namespace Robot
{
	class PatrolTeamEnemy;

	/*
	MonitorState�N���X
	PatrolTeamEnemy�ł̊Ď��p�̌��̓����𐧌䂷��
	*/
	class MonitorState
	{
	protected:

		const double RADIUS        = 40;          // ���̔��a
		const double CHASE_DISTANCE = RADIUS + 20; // �ǂ������n�܂鋗��

	public:

		/// <summary>
		/// �ړ���̎w��
		/// </summary>
		/// <param name="monitorPos"> �Ď��p�̌��̍��W </param>
		virtual void getMoveVec(Vec2 & monitorPos) = 0;

		/// <summary>
		/// �Ď��p�̌��̕`��
		/// </summary>
		/// <param name="monitorPos"> �Ď��p�̌��̍��W </param>
		void drawLight(const Vec2 & monitorPos) const;

		/// <summary>
		/// �����ɉ�������ԑJ�ڂ��s��
		/// </summary>
		virtual void changeState(PatrolTeamEnemy & patrolTeam) = 0;

	};
}