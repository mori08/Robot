#pragma once


#include "../MenuScene.h"


namespace Robot
{
	/*
	StageWindowクラス
	ステージ選択用ウィンドウ
	*/
	class StageWindow : public MenuWindowBase
	{
	private:

		int _buttonNum;

	public:

		StageWindow(MenuScene & menuScene);

	private:

		void draw() const override;

		void updateInputManager() const override;

	};
}