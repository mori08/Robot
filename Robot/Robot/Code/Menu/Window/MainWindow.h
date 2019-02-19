#pragma once


#include "MenuWindowBase.h"


namespace Robot
{
	/*
	MainWindow�N���X
	1�ԏ�ɗ���E�B���h�E
	*/
	class MainWindow : public MenuWindowBase
	{
	public:

		MainWindow();

	private:

		void draw() const override;

		void updateInputManager() const override;

	};
}