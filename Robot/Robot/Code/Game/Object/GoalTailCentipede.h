#pragma once


#include "CentipedeEnemy.h"


namespace Robot
{
	/*
	GoalTailCentipedeƒNƒ‰ƒX
	K”ö‚ªƒS[ƒ‹‚É‚È‚Á‚Ä‚¢‚éƒ€ƒJƒfŒ^‚Ì“G
	*/
	class GoalTailCentipede : public CentipedeEnemy
	{
	private:

		bool _topOrBottom; // ã‚ÉŒü‚©‚¤‚Æ‚« true , ‚»‚¤‚Å‚È‚¢‚Æ‚« false
		Vec2 _goalPos;

	public:

		GoalTailCentipede(const Vec2 & pos);

	private:

		Vec2 getGoalPos() override;

	};
}