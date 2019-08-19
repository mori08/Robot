#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	RandomEnemyクラス
	ランダムに座標を設定して移動する敵
	*/
	class RandomEnemy : public EnemyBase
	{
	private:

		Vec2 _goalPos; // 目的座標

	public:

		/// <summary>
		/// ランダムに座標を設定して移動する敵
		/// </summary>
		/// <param name="pos"> 生成座標 </param>
		RandomEnemy(const Vec2 & pos);

	private:

		Vec2 getMoveVec() override;

	};
}