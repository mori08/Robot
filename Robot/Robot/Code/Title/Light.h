#pragma once


#include<Siv3D.hpp>


namespace Robot
{
	/*
	Lightクラス
	タイトルシーンに流す光
	*/
	class Light
	{
	private:

		Rect  _region;   // 光を表示する範囲

		Point _velocity; // 速度

	private:

		Light(const Point & velocity, const Rect & region);

	public:

		static const Light get();

	public:

		/// <summary>
		/// 位置を更新します。
		/// </summary>
		void update();

		/// <summary>
		/// 描画します。
		/// </summary>
		void draw() const;

		/// <summary>
		/// 削除条件を満たすか示します。
		/// </summary>
		/// <returns> 満たすとき true , そうでないとき false </returns>
		bool isEraseAble() const;

	};
}