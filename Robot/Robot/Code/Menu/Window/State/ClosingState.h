#pragma once


#include "../MenuWindowBase.h"


namespace Robot
{
	/*
	ClosingState�N���X
	�E�B���h�E����鉉�o���s��
	*/
	class ClosingState : public WindowState
	{
	private:

		int _frameCount; // �o�߃t���[����

		Vec2 _offset;    // ���炵

		const Vec2 MAX_OFFSET; // ���炵�̍ő�l

	public:

		ClosingState(const Vec2 & offset);

		void update(MenuWindowBase & window) override;

		void draw(const MenuWindowBase & window) const override;

	};
}