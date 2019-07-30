#pragma once


#include "../PatrolTeamEnemy.h"


namespace Robot
{
	/*
	ChaseMonitorState�N���X
	�v���C���[���������ǂ�������
	*/
	class ChaseMonitorState : public MonitorState
	{
	public:

		void getMoveVec(Vec2 & monitorPos) override;

		void changeState(PatrolTeamEnemy & patrolTeam) override;

	};
}