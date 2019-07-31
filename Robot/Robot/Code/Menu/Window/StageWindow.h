#pragma once


#include "../MenuScene.h"


namespace Robot
{
	/*
	StageWindow�N���X
	�X�e�[�W�I��p�E�B���h�E
	*/
	class StageWindow : public MenuWindowBase
	{
	public:

		StageWindow(MenuScene & menuScene);

	private:

		void draw() const override;

		void updateInputManager() const override;

	};
}