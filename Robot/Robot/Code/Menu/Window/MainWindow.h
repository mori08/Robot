#pragma once


#include "MenuWindowBase.h"


namespace Robot
{
	/*
	MainWindowクラス
	1番上に来るウィンドウ
	*/
	class MainWindow : public MenuWindowBase
	{
	public:

		MainWindow();

	private:

		void updateInputManager() const override;

	};
}