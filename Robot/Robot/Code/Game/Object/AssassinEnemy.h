#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	AssassinEnemyクラス
	プレイヤーに近いと速くに近づく
	光に近いと停止する
	その他はゆっくりプレイヤーに近づく
	*/
	class AssassinEnemy : public EnemyBase
	{
	public:

		AssassinEnemy(const Vec2 & pos);

	private:

		Vec2 getMoveVec(GameManager & gameManager) override;

	};
}