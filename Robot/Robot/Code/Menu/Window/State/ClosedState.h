#pragma once


#include "../MenuWindowBase.h"


namespace Robot
{
	/*
	ClosedStateクラス
	ウィンドウが閉じている状態
	*/
	class ClosedState : public WindowState
	{
	public:

		void update(MenuWindowBase & window) override;

		void draw(const MenuWindowBase & window) const override;

	};
}