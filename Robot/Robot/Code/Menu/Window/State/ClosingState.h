#pragma once


#include "../MenuWindowBase.h"


namespace Robot
{
	/*
	ClosingStateクラス
	ウィンドウを閉じる演出を行う
	*/
	class ClosingState : public WindowState
	{
	private:

		int _frameCount; // 経過フレーム数

		Vec2 _offset;    // ずらし

		const Vec2 MAX_OFFSET; // ずらしの最大値

	public:

		ClosingState(const Vec2 & offset);

		void update(MenuWindowBase & window) override;

		void draw(const MenuWindowBase & window) const override;

	};
}