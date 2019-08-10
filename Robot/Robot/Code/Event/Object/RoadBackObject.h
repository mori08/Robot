#pragma once

#include "EventObject.h"

namespace Robot
{
	/*
	RoadBackObjectクラス
	スクロールさせる道を表示させる
	Actイベントで入口を表示させ、スクロールを止める
	*/
	class RoadBackObject : public EventObject
	{
	private:

		using TextureSet = std::pair<TextureRegion, TextureRegion>;

	private:

		int        _scrollPx; // 画像をずらすx座標

		TextureSet _texture;  // 表示する画像

	public:

		RoadBackObject(const Point & pos);

		void draw(const Vec2 & shakeSize) const override;

	public:

		void scroll();

		void goEntrance();

		void stopEntrance();

	};
}