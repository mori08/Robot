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
		Button(const String & key,const Rect & region);

		/// <summary>
		/// 隣接するボタンを設定します。
		/// </summary>
		/// <param name="direction"> 方向 </param>
		/// <param name="adjacentButton"> 隣接するボタン </param> 
		void setAdjacentButton(int direction, std::shared_ptr<Button> adjacentButton)
		{
#ifdef _DEBUG
			if (direction < 0 || direction > ADJACENT_BUTTON_SIZE)
			{
				Println(L"Error > setAdjuacnetButtonで不適切な入力 : ", direction);
				return;
			}
#endif // _DEBUG

			_adjacentButtonList[direction] = adjacentButton;
		}

		/// <summary>
		/// 隣接するボタンを取得します。
		/// </summary>
		/// <param name="direction"> 方向 </param>
		/// <returns> 隣接するボタンのポインタ </returns>
		std::shared_ptr<Button> getAdjacentButton(int direction) const
		{
#ifdef _DEBUG
			if (direction < 0 || direction > ADJACENT_BUTTON_SIZE)
			{
				Println(L"Error > setAdjuacnetButtonで不適切な入力 : ", direction);
				return nullptr;
			}
#endif // _DEBUG

			return _adjacentButtonList[direction];
		}

		/// <summary>
		/// キーを取得します。
		/// </summary>
		const String & getKey() const
		{
			return _key;
		}

		/// <summary>
		/// マウス入力時の有効範囲を取得します。
		/// </summary>
		/// <return> マウス入力時の有効範囲 </return>
		const Rect & getRegion() const
		{
			return _region;
		}

		/// <summary>
		/// マウス入力時の有効範囲のの左上の点を取得します。
		/// </summary>
		Point getPoint() const
		{
			return _region.pos;
		}

	};
}