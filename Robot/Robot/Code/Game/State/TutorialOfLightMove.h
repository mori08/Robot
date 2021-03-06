#pragma once


#include "PlayingState.h"


namespace Robot
{
	/*
	TutorialOfLightMoveクラス
	光の動作のチュートリアル
	*/
	class TutorialOfLightMove : public PlayingState
	{
	private:

		int _frameCount;     // 経過フレーム数

	public:

		TutorialOfLightMove();

	private:

		void update() override;

		void draw() const override;

	};
}