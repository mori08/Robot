#pragma once


#include "../PatrolTeamEnemy.h"


namespace Robot
{
	/*
	TargetMonitorState�N���X
	�v���C���[�𒆐S���̒��S�ɂȂ�悤��
	�����ړ�������
	*/
	class TargetMonitorState : public MonitorState
	{
	public:

		void getMoveVec(Vec2 & monitorPos) override;

		void changeState(PatrolTeamEnemy & patrolTeam) override;

	};
}