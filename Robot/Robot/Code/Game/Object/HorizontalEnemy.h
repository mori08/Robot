#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	HorizontalEnemyクラス
	水平移動する敵
	*/
	class HorizontalEnemy : public EnemyBase
	{
	private:

		Vec2 _moveVec; // 移動ベクトル

	public:

		/// <summary>
		/// 水平移動する敵
		/// </summary>
		/// <param name="pos"> 生成座標 </param>
		HorizontalEnemy(const Vec2 & pos);

	private:

		Vec2 getMoveVec(GameManager & gameManager) override;

	};
}