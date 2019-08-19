#pragma once


#include "../GameManager.h"


namespace Robot
{
	/*
	TutorialStartState
	チュートリアルのはじめ
	*/
	class TutorialStartState : public GameState
	{
	private:

		int _framecount; // 経過フレーム数

	private:

		void update() override;

		void draw() const override;

	};
}