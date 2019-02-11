#pragma once


#include<Siv3D.hpp>


namespace Robot
{
	/*
	GameLightクラス
	Gameシーンでマップを照らします
	*/
	class GameLight
	{
	private:

		Vec2 _pos; // 光の中心座標

	public:

		/// <summary>
		/// 座標を設定します
		/// </summary>
		/// <param name="pos"> 座標 </param>
		void setPos(const Vec2 & pos)
		{
			_pos = pos;
		}

		/// <summary>
		/// 描画
		/// </summary>
		void update();

		/// <summary>
		/// 描画
		/// </summary>
		void draw() const;

	};
}