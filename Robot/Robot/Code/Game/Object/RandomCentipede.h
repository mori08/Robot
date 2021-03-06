#pragma once


#include "CentipedeEnemy.h"


namespace Robot
{
	/*
	ChaseLightCentibeteクラス
	光を追跡するムカデ型の敵
	*/
	class RandomCentipede : public CentipedeEnemy
	{
	private:

		bool _topOrBottom; // 上に向かうとき true , そうでないとき false
		Vec2 _goalPos;

	public:

		RandomCentipede(const Vec2 & pos);

	private:

		Vec2 getGoalPos() override;

	};
}