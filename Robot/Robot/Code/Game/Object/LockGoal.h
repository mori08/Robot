#pragma once


#include "LockKey.h"


namespace Robot
{
	/*
	LockGoalクラス
	ステージに設置される鍵を全て獲得しないと
	ゴールできない
	*/
	class LockGoal : public GameObject
	{
	private:

		using LockKeyList = std::vector<LockKey>;

	private:

		int   _frameCount; // 経過フレーム数

		int   _lastKeyNum; // 開いていない鍵の数

		Point _texturePos; // 表示する画像の番号

		Vec2  _goal;       // 目的地

		LockKeyList _keyList; // 鍵のリスト

	public:

		/// <summary>
		/// 鍵つきゴール
		/// </summary>
		/// <parma name="pos"> 生成座標 </param>
		LockGoal(const Vec2 & pos);

	private:

		void update() override;

		void draw() const override;

		void drawLight() const override;

		/// <summary>
		/// LockKeyを更新する
		/// </summary>
		void updateKey();

	};
}