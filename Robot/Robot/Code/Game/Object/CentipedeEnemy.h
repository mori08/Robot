#pragma once


#include "CentipedeBody.h"


namespace Robot
{
	/*
	CentipedeEnemyクラス
	ムカデ型の敵
	CentipedeBodyのリストを更新・描画を行う
	*/
	class CentipedeEnemy : public GameObject
	{
	protected:

		std::vector<std::unique_ptr<CentipedeBody>> _bodyList; // 体のパーツリスト

	public:

		CentipedeEnemy(const Vec2 & pos)
			: GameObject(pos)
		{
		}

		void update() override;

		void draw() const override;

	protected:

		/// <summary>
		/// 目的地の座標を取得します。
		/// </summary>
		virtual Vec2 getGoalPos() = 0;

	};
}