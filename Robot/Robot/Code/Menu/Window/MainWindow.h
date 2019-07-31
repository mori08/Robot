#pragma once


#include "../MenuScene.h"


namespace Robot
{
	/*
	MainWindowクラス
	1番上に来るウィンドウ
	*/
	class MainWindow : public MenuWindowBase
	{
	public:

		MainWindow(MenuScene & menuScene);

	private:

		void updateInputManager() const override;

	};
}