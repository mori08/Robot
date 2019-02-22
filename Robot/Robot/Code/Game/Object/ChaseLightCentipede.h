#pragma once


#include "CentipedeEnemy.h"


namespace Robot
{
	/*
	ChaseLightCentibeteクラス
	光を追跡するムカデ型の敵
	*/
	class ChaseLightCentipede : public CentipedeEnemy
	{
	public:

		ChaseLightCentipede(const Vec2 & pos);

	private:

		Vec2 getGoalPos() override;

	};
}