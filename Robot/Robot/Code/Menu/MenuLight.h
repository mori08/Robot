#pragma once


#include <Siv3D.hpp>


namespace Robot
{
	/*
	MenuLightクラス
	メニューシーンに流す光
	*/
	class MenuLight
	{
	private:

		Circle _region; // 光を表示する範囲

		double _speed;  // 速さ

		int    _alpha;  // 色

	private:

		/// <param name="x"> 生成するx座標 </param>
		/// <param name="r"> 半径(速さはこれの二乗に比例) </param>
		MenuLight(double x, double r);

	public:

		bool operator<(const MenuLight & light) const;

	public:

		static const MenuLight get();

	public:

		/// <summary>
		/// 更新
		/// </summary>
		void update();

		/// <summary>
		/// 描画
		/// </summary>
		void draw() const;

		/// <summary>
		/// 削除条件を満たすか示します。
		/// </summary>
		/// <returns> 満たすとき true , そうでないとき false </returns>
		bool isEraseAble() const;

	};
}