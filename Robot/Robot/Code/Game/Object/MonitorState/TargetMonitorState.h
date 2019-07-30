#pragma once


#include "../PatrolTeamEnemy.h"


namespace Robot
{
	/*
	TargetMonitorStateクラス
	プレイヤーを中心光の中心になるように
	光を移動させる
	*/
	class TargetMonitorState : public MonitorState
	{
	public:

		void getMoveVec(Vec2 & monitorPos) override;

		void changeState(PatrolTeamEnemy & patrolTeam) override;

	};
}