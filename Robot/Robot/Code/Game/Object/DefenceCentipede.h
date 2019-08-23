#pragma once


#include "CentipedeEnemy.h"


namespace Robot
{
	/*
	DefenceCentipedeƒNƒ‰ƒX
	ƒS[ƒ‹‚Ìü•Ó‚ğ’Ç‚¢‘±‚¯‚Ü‚·
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