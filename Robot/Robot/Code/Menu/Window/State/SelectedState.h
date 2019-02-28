#pragma once


#include "../MenuWindowBase.h"


namespace Robot
{
	/*
	SelectedState�N���X
	�E�B���h�E���I������Ă�����
	*/
	class SelectedState : public WindowState
	{
	public:

		void update(MenuWindowBase & window) override;

		void draw(const MenuWindowBase & window) const override;

	};
}