#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	VerticalBlockEnemyクラス
	プレイヤーのy座標を追跡する
	*/
	class VerticalBlockEnemy : public EnemyBase
	{
	public:

		/// <summary>
		/// プレイヤーのx座標を追跡する敵
		/// </summary>
		/// <param name="pos"> 生成座標 </param>
		VerticalBlockEnemy(const Vec2 & pos);

	private:

		Vec2 getMoveVec() override;

	};
}
