#pragma once

#include "EventState.h"


namespace Robot
{
	/*
	PlayEventStateクラス
	イベントを実行している状態
	*/
	class PlayEventState : public EventState
	{
	public:

		void update() override;

		void draw() const override;

	};
}