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

		bool _off; // trueのときライトを消す

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
		/// 座標を取得します。
		/// </summary>
		/// <returns> 座標 </returns>
		const Vec2 & getPos() const
		{
			return _pos;
		}

		/// <summary>
		/// ライトを消す
		/// </summary>
		void Off()
		{
			_off = true;
		}

		/// <summary>
		/// ライトをつける
		/// </summary>
		void On()
		{
			_off = false;
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