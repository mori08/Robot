#pragma once


#include "../MenuScene.h"


namespace Robot
{
	/*
	MainWindow�N���X
	1�ԏ�ɗ���E�B���h�E
	*/
	class MainWindow : public MenuWindowBase
	{
	public:

		MainWindow(MenuScene & menuScene);

	private:

		void updateInputManager() const override;

	};
}