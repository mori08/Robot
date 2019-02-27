#pragma once


#include "../MenuWindowBase.h"


namespace Robot
{
	/*
	OpenedStateクラス
	ウィンドウが開かれているが選択されていない状態
	*/
	class OpenedState : public WindowState
	{
	public:

		void update(MenuWindowBase & window) override;

		void draw(const MenuWindowBase & window) const override;

	};
}