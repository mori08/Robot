#pragma once


#include "PlayingState.h"


namespace Robot
{
	/*
	TutorialStartState
	チュートリアルのはじめ
	*/
	class TutorialStartState : public PlayingState
	{
	private:

		int _framecount; // 経過フレーム数

	private:

		void update() override;

		void draw() const override;

	};
}