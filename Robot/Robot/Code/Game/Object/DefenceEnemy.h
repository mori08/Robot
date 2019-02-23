#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	DefenceEnemyクラス
	ゴールを守る敵
	*/
	class DefenceEnemy : public EnemyBase
	{
	private:

		bool _attackOrDefence; // trueのときプレイヤーを追いかけ , falseのときゴールを追いかける

	public:

		/// <summary>
		/// ゴールを守る敵
		/// </summary>
		/// <param name="pos"> 生成座標 </param>
		DefenceEnemy(const Vec2 & pos);

	private:

		Vec2 getMoveVec(GameManager & gameManager) override;

	};
}