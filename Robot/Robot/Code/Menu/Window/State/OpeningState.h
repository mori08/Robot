#pragma once


#include "../MenuWindowBase.h"


namespace Robot
{
	/*
	OpeningState�N���X
	�E�B���h�E���J�����o��ǉ�
	*/
	class OpeningState : public WindowState
	{
	private:

		int  _frameCount; // �o�߃t���[����

		Vec2 _offset;     // ���炵

	public:

		OpeningState(const Vec2 & offset);

		void update(MenuWindowBase & window) override;

		void draw(const MenuWindowBase & window) const override;

	};
}