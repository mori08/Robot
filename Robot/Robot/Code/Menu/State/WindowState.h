#pragma once


#include <Siv3D.hpp>


namespace Robot
{
	class MenuWindowBase;

	/*
	WindowStateクラス
	ウィンドウの状態を表現します
	*/
	class WindowState
	{
	public:

		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="window"> ウィンドウ </param>
		virtual void update(MenuWindowBase & window) = 0;

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="window"> ウィンドウ </param>
		virtual void draw(const MenuWindowBase & window) const = 0;

	};
}