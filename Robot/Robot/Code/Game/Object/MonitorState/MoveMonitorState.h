#pragma once


#include "../PatrolTeamEnemy.h"


namespace Robot
{
	/*
	MoveMonitorState�N���X
	���j�^�[�������_���Ō��肵���ړI�n�Ɉړ�������
	*/
	class MoveMonitorState : public MonitorState
	{
	private:

		Vec2 _goal; // �ړI�n

	public:

		MoveMonitorState();

		void getMoveVec(Vec2 & monitorPos) override;

		void changeState(PatrolTeamEnemy & patrolTeam) override;

	};
}