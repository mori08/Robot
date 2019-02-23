#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	HorizontalBlockEnemyクラス
	プレイヤーのx座標を追跡する
	*/
	class HorizontalBlockEnemy : public EnemyBase
	{
	public:

		/// <summary>
		/// プレイヤーのx座標を追跡する敵
		/// </summary>
		/// <param name="pos"> 生成座標 </param>
		HorizontalBlockEnemy(const Vec2 & pos);

	private:

		Vec2 getMoveVec(GameManager & gameManager) override;

	};
}