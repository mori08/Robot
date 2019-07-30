#pragma once


#include "../PatrolTeamEnemy.h"


namespace Robot
{
	/*
	StayMonitorState�N���X
	���j�^�[����莞�ԐÎ~�����Ă���
	*/
	class StayMonitorState : public MonitorState
	{
	private:

		int _stayFrameCount; // �c���~����(�t���[����)

	public:

		StayMonitorState();

		void getMoveVec(Vec2 & monitorPos) override;

		void changeState(PatrolTeamEnemy & patrolTeam) override;
	};

}