#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	DefenceEnemyNX
	S[๐็้G
	*/
	class DefenceEnemy : public EnemyBase
	{
	public:

		/// <summary>
		/// S[๐็้G
		/// </summary>
		/// <param name="pos"> ถฌภW </param>
		DefenceEnemy(const Vec2 & pos);

	private:

		Vec2 getMoveVec() override;

	};
}