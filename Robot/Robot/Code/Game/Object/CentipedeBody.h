#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	CentipedeBodyクラス
	CentipedeEnemyの部品
	目的地を設定してそれを追わせる
	*/
	class CentipedeBody : public GameObject
	{
	protected:

		Vec2 _goalPos;    // 目的座標

		int  _frameCount; // 経過フレーム数

	public:

		/// <summary>
		/// CentipedeEnemyの部品
		/// </summary>
		/// <param name="pos"> 目的座標 </para,>
		CentipedeBody(const Vec2 & pos);

		virtual void update() override;

		virtual void draw() const override;

		/// <summary>
		/// 座標を取得します。
		/// </summary>
		const Vec2 & getPos() const
		{
			return _pos;
		}

		/// <summary>
		/// 目的座標を設定します。
		/// </summary>
		/// <param name="pos"> 座標 </param>
		void setGoalPos(const Vec2 & pos)
		{
			_goalPos = pos;
		}

	protected:

		/// <summary>
		/// プレイヤーと接触したときの処理
		/// </summary>
		virtual void connectedPlayerProcess();

	};
}