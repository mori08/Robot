#pragma once


#include "EventState.h"
#include <Siv3D.hpp>


namespace Robot
{
	/*
	PauseEventStateクラス
	イベントを一時中止し、
	続ける・スキップする・メニュー
	を選択する
	*/
	class PauseEventState : public EventState
	{
	private:

		RectF _cursor;

	public:

		PauseEventState();

		void update() override;

		void draw() const override;

	private:

		void drawButtonName(int y, const String & name) const;

	};
}