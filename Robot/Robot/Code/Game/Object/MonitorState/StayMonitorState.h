#pragma once


#include "../PatrolTeamEnemy.h"


namespace Robot
{
	/*
	StayMonitorStateクラス
	モニターを一定時間静止させておく
	*/
	class StayMonitorState : public MonitorState
	{
	private:

		int _stayFrameCount; // 残り停止時間(フレーム数)

	public:

		StayMonitorState();

		void getMoveVec(Vec2 & monitorPos) override;

		void changeState(PatrolTeamEnemy & patrolTeam) override;
	};

}