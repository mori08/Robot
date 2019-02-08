#pragma once


#include<Siv3D.hpp>


namespace Robot
{
	class GameManager;

	class GameObject
	{
	protected:
		
		Vec2 _pos; // 座標

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
		/// <param name="gameManager"> GameManagerのインスタンス </param>
		virtual void update(GameManager & gameManager) = 0;

		/// <summary>
		/// 描画
		/// </summary>
		virtual void draw() const = 0;

	};
}