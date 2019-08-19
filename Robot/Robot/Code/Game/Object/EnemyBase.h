#pragma once


#include "../GameManager.h"


namespace Robot
{
	/*
	EnemyBaseクラス
	GameObjectクラスの派生クラス
	作成する敵の基底クラスとなり
	プレイヤーとぶつかったときの処理
	敵の画像の描画
	*/
	class EnemyBase : public GameObject
	{
	protected:

		int   _frameCount; // 経過フレーム数

		Point _texturePos; // 描画する画像の番号

	public:

		EnemyBase(const Vec2 & pos);

		virtual void update() override;

		virtual void draw() const override;

	protected:

		/// <summary>
		/// 移動ベクトルを決めます。
		/// </summary>
		/// <returns> 移動ベクトル </returns>
		virtual Vec2 getMoveVec() = 0;

		/// <summary>
		/// プレイヤーと接触したときの処理
		/// </summary>
		virtual void gameOver()
		{
			GameManager::Instance().gameOver();
		}

	};
}