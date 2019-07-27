#pragma once


#include "EnemyBase.h"


namespace Robot
{
	/*
	DoctorDefenceクラス
	DoctorGoalクラスの周囲をまわる
	プレイヤーがDoctorGoalに近づいたら追跡する
	*/
	class DoctorDefence : public EnemyBase
	{
	private :

		Vec2 _defencePos; // ゴールを守るための位置

	public:

		DoctorDefence(const Vec2 & pos);

		/// <summary>
		/// _defencePosの設定
		/// </summary>
		/// <param name="pos"> 座標 </param>
		void setDefencePos(const Vec2 & pos);

		/// <summary>
		/// 座標を取得
		/// </summary>
		Vec2 getPos() const
		{
			return _pos;
		}

	private:

		Vec2 getMoveVec(GameManager & gameManager) override;

	};

}