#pragma once


#include "CentipedeEnemy.h"


namespace Robot
{
	/*
	GoalTailCentipedeクラス
	尻尾がゴールになっているムカデ型の敵
	*/
	class GoalTailCentipede : public CentipedeEnemy
	{
	private:

		bool _topOrBottom; // 上に向かうとき true , そうでないとき false
		Vec2 _goalPos;

	public:

		GoalTailCentipede(const Vec2 & pos);

	private:

		Vec2 getGoalPos() override;

	};
}