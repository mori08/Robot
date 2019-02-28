#pragma once


#include "../MenuWindowBase.h"


namespace Robot
{
	/*
	SelectedStateクラス
	ウィンドウが選択されている状態
	*/
	class SelectedState : public WindowState
	{
	public:

		void update(MenuWindowBase & window) override;

		void draw(const MenuWindowBase & window) const override;

	};
}