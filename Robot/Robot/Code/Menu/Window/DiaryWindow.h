#pragma once


#include "../MenuScene.h"


namespace Robot
{
	/*
	DiaryWindowクラス
	イベントの再読み込み
	*/
	class DiaryWindow : public MenuWindowBase
	{
	private:

		int _stageNum;

	public:

		DiaryWindow(MenuScene & menuScene);

	private:

		void draw() const override;

		void updateInputManager() const override;

	};
}