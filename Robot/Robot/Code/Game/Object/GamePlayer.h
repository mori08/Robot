#pragma once


#include"../GameManager.h"


namespace Robot
{
	/*
	GamePlayerクラス
	GameObjectの派生クラスで，
	GameManagerでPlayerとして扱う．
	キー入力に応じた移動をする．
	*/
	class GamePlayer : public GameObject 
	{
	private:

		double _lightCircleRate; // 光の輪を表現する値(0~1)

	public:

		/// <summary>
		/// GameManagerでのPlayerオブジェクト
		/// </summary>
		/// <param name="pos"> 生成座標 </param>
		GamePlayer(const Vec2 & pos);

	private:

		void update(GameManager & gameManager) override;

		void draw() const override;

		void drawLight() const override;

		/// <summary>
		/// プレイヤーの移動方向をキー入力から決定します。
		/// </summary>
		/// <returns> 移動方向 </returns>
		Vec2 getMoveVec() const;

	};
}