#pragma once


#include<Siv3D.hpp>


namespace Robot
{
	/*
	TitleLightクラス
	タイトルシーンに流す光
	*/
	class TitleLight
	{
	private:

		Rect  _region;   // 光を表示する範囲

		Point _velocity; // 速度

	private:

		TitleLight(const Point & velocity, const Rect & region);

	public:

		static const TitleLight get();

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