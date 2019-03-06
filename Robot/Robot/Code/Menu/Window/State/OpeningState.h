#pragma once


#include "../MenuWindowBase.h"


namespace Robot
{
	/*
	OpeningStateクラス
	ウィンドウを開く演出を追加
	*/
	class OpeningState : public WindowState
	{
	private:

		int  _frameCount; // 経過フレーム数

		Vec2 _offset;     // ずらし

	public:

		OpeningState(const Vec2 & offset);

		void update(MenuWindowBase & window) override;

		void draw(const MenuWindowBase & window) const override;

	};
}