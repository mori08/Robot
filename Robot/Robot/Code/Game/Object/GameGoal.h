#pragma once


#include"../GameManager.h"


namespace Robot
{
	/*
	GameGaolクラス
	Playerがこのオブジェクトに触れた時
	クリアとなります。
	*/
	class GameGoal : public GameObject
	{
	private:

		int   _frameCount; // 経過フレーム数

		Point _texturePos; // 表示する画像の番号

	public:

		/// <summary>
		/// ゲームでのゴール
		/// </summary>
		/// <param name="pos"> 生成座標 </param>
		GameGoal(const Vec2 & pos)
			: GameObject(pos)
			, _texturePos(Point::Zero)
			, _frameCount(0)
		{

		}

	private:

		void update(GameManager & gameManager) override;

		void draw() const override;

	protected:

		/// <summary>
		/// 移動ベクトルを取得します。
		/// </summary>
		/// <param name="gameManager"> GameManagerクラスのインスタンス </param>
		virtual Vec2 getMoveVec(GameManager &)
		{
			return Vec2::Zero;
		}

	};
}