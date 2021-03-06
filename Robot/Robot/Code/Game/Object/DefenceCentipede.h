#pragma once


#include "CentipedeEnemy.h"


namespace Robot
{
	/*
	DefenceCentipedeクラス
	ゴールの周辺を追い続けます
	*/
	class DefenceCentipede : public CentipedeEnemy
	{
	private:

		Vec2 _goalPos;

	public:

		DefenceCentipede(const Vec2 & pos);

	private:

		Vec2 getGoalPos() override;

	};
}