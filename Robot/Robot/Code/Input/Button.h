#pragma once


#include<Siv3D.hpp>


namespace Robot
{

	/*
	Buttonクラス
	隣接するボタンや上にカーソルがあるかなどを示します。
	InputManagerクラスで使用します。
	*/

	class Button
	{
	private:

		static const int ADJACENT_BUTTON_SIZE = 4;                                     // 隣接するボタンの数

		std::array<std::shared_ptr<Button>, ADJACENT_BUTTON_SIZE> _adjacentButtonList; // 隣接するボタンのポインタ

		const String _key;    // 出力用のキー

		const Rect   _region; // マウス入力時の有効範囲

	public:

		static const int UP    = 0; // 上
		static const int DOWN  = 1; // 下
		static const int LEFT  = 2; // 左
		static const int RIGHT = 3; // 右

	public:

		/// <summary>
		/// ボタン
		/// </summary>
		/// <param name="key"> 出力用のキー </param>
		/// <param name="region"> マウス入力時の有効範囲 </param>
		Button(const String & key,const Rect region);

		/// <summary>
		/// 隣接するボタンを設定します。
		/// </summary>
		/// <param name="direction"> 方向 </param>
		/// <param name="adjacentButton"> 隣接するボタン </param> 
		void setAdjacentButton(int direction, std::shared_ptr<Button> adjacentButton);

		/// <summary>
		/// カーソルが上にあるかを示します。
		/// </summary>
		/// <returns> カーソルが上にあるとき true , そうでないとき false </returns>
		bool mouseOver() const
		{
			return _region.mouseOver;
		}
	};
}