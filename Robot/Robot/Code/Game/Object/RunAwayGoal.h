#pragma once


#include "GameGoal.h"


namespace Robot
{
	/*
	RunAwayGoalクラス
	プレイヤーから逃げるゴール
	*/
	class RunAwayGoal : public GameGoal
	{
	private:

		std::vector<Point> _runPointList; // 逃げ座標リスト
		int                _goalPointId;  // 目的座標

	public:

		RunAwayGoal(const Vec2 & pos);

	private:

		Vec2 getMoveVec() override;

	};
}