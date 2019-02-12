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
	public:

		/// <summary>
		/// GameManagerでのPlayerオブジェクト
		/// </summary>
		/// <param name="pos"> 生成座標 </param>
		GamePlayer(const Vec2 & pos);

	private:

		void update(GameManager & gameManager) override;

		void draw() const override;

		/// <summary>
		/// プレイヤーの移動方向をキー入力から決定します。
		/// </summary>
		/// <returns> 移動方向 </returns>
		Vec2 getMoveVec() const;

	};
}