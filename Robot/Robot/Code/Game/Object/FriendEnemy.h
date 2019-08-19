#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	FriendEnemyクラス
	ステージを完全に照らす
	ステージを揺らす
	少しずつスピードを上げる
	*/
	class FriendEnemy : public EnemyBase
	{
	private:

		double _speed;      // 速さ

		int    _shake;      // 画面の揺れの大きさ

	public:

		FriendEnemy(const Vec2 & pos);

	private:

		void drawLight() const override;

		Vec2 getMoveVec() override;

		void gameOver() override
		{
			GameManager::Instance().lose();
		}

	};
}