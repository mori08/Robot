#pragma once


#include "../MenuWindowBase.h"


namespace Robot
{
	/*
	OpenedState�N���X
	�E�B���h�E���J����Ă��邪�I������Ă��Ȃ����
	*/
	class OpenedState : public WindowState
	{
	public:

		void update(MenuWindowBase & window) override;

		void draw(const MenuWindowBase & window) const override;

	};
}