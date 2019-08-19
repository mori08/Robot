#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	VerticalEnemyクラス
	垂直移動する敵
	*/
	class VerticalEnemy : public EnemyBase
	{
	private:

		Vec2 _moveVec; // 移動ベクトル

	public:

		/// <summary>
		/// 垂直移動する敵
		/// </summary>
		/// <param name="pos"> 生成座標 </param>
		VerticalEnemy(const Vec2 & pos);

	private:

		Vec2 getMoveVec() override;

	};
}