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

		int _frameCount; // �o�߃t���[����

		std::vector<Vec2>   _offsetList; // ���炵

		std::vector<double> _alphaList;  // �s�����x

	public:

		OpeningState(size_t numOfButton, const Vec2 & offset);

		void update(MenuWindowBase & window) override;

		void draw(const MenuWindowBase & window) const override;

	};
}