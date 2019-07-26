#pragma once


#include"EnemyBase.h"


namespace Robot
{
	/*
	FlashEnemyクラス
	発光したあとプレイヤーを追いかける
	*/
	class FlashEnemy : public EnemyBase
	{
	private:

		int  _changeMoveFramecount; // 行動パターンをこの値に応じて変更

		Vec2 _goalPos;              // 発光時でないときの目的地

	public:

		FlashEnemy(const Vec2 & pos);

	private:

		Vec2 getMoveVec(GameManager & gameManager) override;

		void drawLight() const;

	};
}