#pragma once


#include "GameGoal.h"


namespace Robot
{
	/*
	LastGoalクラス
	最終ステージ(9番目)に使用するゴール
	ステージの4角のうプレイヤーから遠い場所を計算する
	*/
	class LastGoal : public GameGoal
	{
	private:

		int _goalPosIndex;              // 今向かっている目的地の番号
		std::vector<Vec2> _goalPosList; // 四つ角

	public:

		LastGoal(const Vec2 & pos);

	private:

		Vec2 getMoveVec(GameManager & gameManager) override;

	};
}