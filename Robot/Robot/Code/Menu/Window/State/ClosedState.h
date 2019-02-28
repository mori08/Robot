#pragma once


#include "../MenuWindowBase.h"


namespace Robot
{
	/*
	ClosedState�N���X
	�E�B���h�E�����Ă�����
	*/
	class ClosedState : public WindowState
	{
	public:

		void update(MenuWindowBase & window) override;

		void draw(const MenuWindowBase & window) const override;

	};
}