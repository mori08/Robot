#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	ChaseEnemyクラス
	プレイヤーを追跡する敵
	*/
	class ChaseEnemy : public EnemyBase
	{
	public:

		/// <summary>
		/// プレイヤーを追跡する敵
		/// </summary>
		/// <param name="pos"> 生成座標 </param>
		ChaseEnemy(const Vec2 & pos);

	private:

		Vec2 getMoveVec() override;

	};
}