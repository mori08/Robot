#pragma once


#include "MenuWindowBase.h"


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

		DiaryWindow();

	private:

		void draw() const override;

		void updateInputManager() const override;

		void makeButton() override;

	};
}