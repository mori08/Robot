#pragma once


#include "../PatrolTeamEnemy.h"


namespace Robot
{
	/*
	MoveMonitorStateクラス
	モニターをランダムで決定した目的地に移動させる
	*/
	class MoveMonitorState : public MonitorState
	{
	private:

		Vec2 _goal; // 目的地

	public:

		MoveMonitorState();

		void getMoveVec(Vec2 & monitorPos) override;

		void changeState(PatrolTeamEnemy & patrolTeam) override;

	};
}