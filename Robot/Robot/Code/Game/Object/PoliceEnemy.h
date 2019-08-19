#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	PoliceEnemyクラス
	PatrolTeamEnemyクラスで使用する
	*/
	class PoliceEnemy : public EnemyBase
	{
	private:

		bool _isChasing; // 追いかけているとき true

		const Vec2 _startPos;  // 持場

	public:

		PoliceEnemy(const Vec2 & pos);

		void drawLight() const override;

		/// <summary>
		/// 動き方を変更する
		/// </summary>
		/// <param name="isChasing">
		/// true ならプレイヤーを追いかける , false なら持場にもどる
		/// </param>
		void setChase(const bool isChasing)
		{
			_isChasing = isChasing;
		}

	private:

		Vec2 getMoveVec() override;

	};
}