#pragma once


#include "CentipedeBody.h"


namespace Robot
{
	/*
	CentipedeBodyクラス
	CentipedeEnemyの部品
	敵ではなくゴールとしての機能を持たせる
	*/
	class CentipedeGoalBody : public CentipedeBody
	{
	public:

		/// <summary>
		/// ゴールとしての機能するムカデ型の敵の部品
		/// </summary>
		/// <param name="pos"> 生成座標 </param>
		CentipedeGoalBody(const Vec2 & pos);

	private:

		void update() override;

		void draw() const override;

		void connectedPlayerProcess() override;

	};
}