#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	GiantEnemyクラス
	巨大な敵
	*/
	class GiantEnemy : public EnemyBase
	{
	private:

		int   _frameCount; // 経過フレーム数

		Point _texturePos; // 描画する画像の番号

		Vec2  _goalPos;    // 目的座標

	public:

		/// <sumamry>
		/// 巨大な敵
		/// </summary>
		/// <param name="pos"> 生成座標 </param>
		GiantEnemy(const Vec2 & pos);

	private:

		void update(GameManager & gameManager) override;

		void draw() const override;

		Vec2 getMoveVec(GameManager & gameManager) override;

	};
}