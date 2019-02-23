#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	DefenceEnemyƒNƒ‰ƒX
	ƒS[ƒ‹‚ğç‚é“G
	*/
	class DefenceEnemy : public EnemyBase
	{
	public:

		/// <summary>
		/// ƒS[ƒ‹‚ğç‚é“G
		/// </summary>
		/// <param name="pos"> ¶¬À•W </param>
		DefenceEnemy(const Vec2 & pos);

	private:

		Vec2 getMoveVec(GameManager & gameManager) override;

	};
}