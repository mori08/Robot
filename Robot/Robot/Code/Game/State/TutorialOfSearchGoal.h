#pragma once


#include "../GameManager.h"


namespace Robot
{
	/*
	TutorialOfSearchGoalクラス
	ゴールの探索のチュートリアル
	*/
	class TutorialOfSearchGoal : public GameState
	{
	private:

		size_t _frameCount; // 経過フレーム数

	public:

		TutorialOfSearchGoal();

	private:

		void update() override;

		void draw() const override;

	};
}