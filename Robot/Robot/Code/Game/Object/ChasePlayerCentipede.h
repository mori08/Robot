#pragma once


#include "CentipedeEnemy.h"


namespace Robot
{
	/*
	ChasePlayerCentibeteクラス
	プレイヤーを追跡するムカデ型の敵
	*/
	class ChasePlayerCentipede : public CentipedeEnemy
	{
	public:

		ChasePlayerCentipede(const Vec2 & pos);

	private:

		Vec2 getGoalPos() override;

	};
}