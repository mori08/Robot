#pragma once


#include "MenuWindowBase.h"


namespace Robot
{
	/*
	StageWindow�N���X
	�X�e�[�W�I��p�E�B���h�E
	*/
	class StageWindow : public MenuWindowBase
	{
	private:

		int _buttonNum;

	public:

		StageWindow();

	private:

		void draw() const override;

		void updateInputManager() const override;

		void makeButton() override;

	};
}