#pragma once


#include "../PatrolTeamEnemy.h"


namespace Robot
{
	/*
	ChaseMonitorStateクラス
	プレイヤーをゆっくり追いかける
	*/
	class ChaseMonitorState : public MonitorState
	{
	public:

		void getMoveVec(Vec2 & monitorPos) override;

		void changeState(PatrolTeamEnemy & patrolTeam) override;

	};
}