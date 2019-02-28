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

		int _frameCount; // 経過フレーム数

		std::vector<Vec2>   _offsetList; // ずらし

		std::vector<double> _alphaList;  // 不透明度

	public:

		OpeningState(size_t numOfButton, const Vec2 & offset);

		void update(MenuWindowBase & window) override;

		void draw(const MenuWindowBase & window) const override;

	};
}