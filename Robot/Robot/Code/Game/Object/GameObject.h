#pragma once


#include<Siv3D.hpp>


namespace Robot
{
	class GameManager;

	/*
	GameObjectクラス
	GameManagerで扱うObject(プレイヤー・敵・ゴールなど)の基底クラス
	このクラスの派生クラスを作成するときは
	GameManagerのObject生成関数に登録する
	*/
	class GameObject
	{
	protected:
		
		Vec2 _pos;     // 座標

	public:

		/// <summary>
		/// ゲームシーンで扱うオブジェクト
		/// </summary>
		GameObject(const Vec2 & pos)
			: _pos(pos)
		{
		}

		/// <summary>
		/// 更新
		/// </summary>
		virtual void update() = 0;

		/// <summary>
		/// 描画
		/// </summary>
		virtual void draw() const = 0;

		/// <summary>
		/// 光の描画
		/// </summary>
		virtual void drawLight() const
		{
		}

	protected:

		/// <summary>
		/// オブジェクトの位置を移動させます。
		/// </summary>
		/// <param name="vec"> 加算する座標 </param>
		void moveObject(const Vec2 & vec);

	};
}