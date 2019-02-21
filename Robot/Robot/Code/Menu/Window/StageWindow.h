#pragma once


#include "MenuWindowBase.h"


namespace Robot
{
	/*
	StageWindowクラス
	ステージ選択用ウィンドウ
	*/
	class StageWindow : public MenuWindowBase
	{
	public:

		StageWindow();

	private:

		void draw() const override;

		void updateInputManager() const override;

	};
}